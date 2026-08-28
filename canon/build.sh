#!/usr/bin/env bash
set -euo pipefail

DEMO_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${DEMO_DIR}/build"
COMPILER_INPUT="${SYSY_COMPILER:-}"
CONTAINER_IMAGE="${SYSY_COMPILER_DEV_IMAGE:-maxxing/compiler-dev}"

if [[ -z "${COMPILER_INPUT}" ]]; then
  echo "usage: SYSY_COMPILER=/absolute/path/to/compiler ./build.sh" >&2
  exit 2
fi

if [[ -x "${COMPILER_INPUT}" ]]; then
  COMPILER_BIN="$(cd -- "$(dirname -- "${COMPILER_INPUT}")" && pwd)/$(basename -- "${COMPILER_INPUT}")"
elif command -v "${COMPILER_INPUT}" >/dev/null 2>&1; then
  COMPILER_BIN="$(command -v "${COMPILER_INPUT}")"
else
  echo "error: SysY compiler is not executable: ${COMPILER_INPUT}" >&2
  exit 2
fi

for tool in docker ffmpeg; do
  if ! command -v "${tool}" >/dev/null 2>&1; then
    echo "error: required tool not found: ${tool}" >&2
    exit 2
  fi
done

mkdir -p "${BUILD_DIR}"

echo "[1/4] Compiling pure SysY audio and video renderers"
"${COMPILER_BIN}" -riscv "${DEMO_DIR}/score2wav.c" -o "${BUILD_DIR}/score2wav.S"
"${COMPILER_BIN}" -riscv "${DEMO_DIR}/visualizer.c" -o "${BUILD_DIR}/visualizer.S"

echo "[2/4] Assembling and linking RV32 executables"
docker run --rm \
  --user "$(id -u):$(id -g)" \
  -v "${DEMO_DIR}:/work" \
  -w /work \
  "${CONTAINER_IMAGE}" \
  sh -lc '
    clang build/score2wav.S -c -o build/score2wav.o \
      -target riscv32-unknown-linux-elf -march=rv32im -mabi=ilp32 &&
    ld.lld build/score2wav.o -L/opt/lib/riscv32 -lsysy \
      -o build/score2wav-riscv &&
    clang build/visualizer.S -c -o build/visualizer.o \
      -target riscv32-unknown-linux-elf -march=rv32im -mabi=ilp32 &&
    ld.lld build/visualizer.o -L/opt/lib/riscv32 -lsysy \
      -o build/visualizer-riscv
  '

echo "[3/4] Rendering WAV and Y4M directly under QEMU"
docker run --rm -i \
  --user "$(id -u):$(id -g)" \
  -v "${DEMO_DIR}:/work" \
  -w /work \
  "${CONTAINER_IMAGE}" \
  qemu-riscv32-static build/score2wav-riscv \
  < "${DEMO_DIR}/canon.mml" \
  > "${BUILD_DIR}/canon.wav"
docker run --rm \
  --user "$(id -u):$(id -g)" \
  -v "${DEMO_DIR}:/work" \
  -w /work \
  "${CONTAINER_IMAGE}" \
  sh -lc 'qemu-riscv32-static build/visualizer-riscv > build/visualizer.y4m'

echo "[4/4] Encoding and muxing the final video with FFmpeg"
ffmpeg -y -v warning \
  -i "${BUILD_DIR}/visualizer.y4m" \
  -i "${BUILD_DIR}/canon.wav" \
  -c:v libx264 -preset medium -crf 18 -pix_fmt yuv420p \
  -c:a aac -b:a 128k -shortest \
  "${BUILD_DIR}/canon-demo.mp4"

echo "done:"
echo "  ${BUILD_DIR}/canon.wav"
echo "  ${BUILD_DIR}/canon-demo.mp4"
