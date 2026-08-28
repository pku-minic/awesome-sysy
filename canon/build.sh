#!/usr/bin/env bash
set -euo pipefail

DEMO_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${DEMO_DIR}/build"
COMPILER_INPUT="${SYSY_COMPILER:-${1:-}}"
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

echo "[1/5] Compiling SysY sources to RISC-V assembly"
"${COMPILER_BIN}" -riscv "${DEMO_DIR}/canon.c" -o "${BUILD_DIR}/canon.S"
"${COMPILER_BIN}" -riscv "${DEMO_DIR}/visualizer.c" -o "${BUILD_DIR}/visualizer.S"

echo "[2/5] Assembling and linking RV32 executables"
docker run --rm \
  --user "$(id -u):$(id -g)" \
  -v "${DEMO_DIR}:/work" \
  -w /work \
  "${CONTAINER_IMAGE}" \
  sh -lc '
    clang build/canon.S -c -o build/canon.o \
      -target riscv32-unknown-linux-elf -march=rv32im -mabi=ilp32 &&
    ld.lld build/canon.o -L/opt/lib/riscv32 -lsysy -o build/canon-riscv &&
    clang build/visualizer.S -c -o build/visualizer.o \
      -target riscv32-unknown-linux-elf -march=rv32im -mabi=ilp32 &&
    ld.lld build/visualizer.o -L/opt/lib/riscv32 -lsysy \
      -o build/visualizer-riscv
  '

echo "[3/5] Rendering audio and video under QEMU"
docker run --rm \
  --user "$(id -u):$(id -g)" \
  -v "${DEMO_DIR}:/work" \
  -w /work \
  "${CONTAINER_IMAGE}" \
  sh -lc '
    qemu-riscv32-static build/canon-riscv > canon.wav &&
    qemu-riscv32-static build/visualizer-riscv > build/visualizer.y4m
  '

echo "[4/5] Encoding and muxing MP4"
ffmpeg -y -v warning \
  -i "${BUILD_DIR}/visualizer.y4m" \
  -i "${DEMO_DIR}/canon.wav" \
  -c:v libx264 -preset medium -crf 18 -pix_fmt yuv420p \
  -c:a aac -b:a 128k -shortest \
  "${DEMO_DIR}/canon-demo.mp4"

echo "[5/5] Generating preview image"
ffmpeg -y -v error \
  -ss 15 \
  -i "${DEMO_DIR}/canon-demo.mp4" \
  -frames:v 1 \
  "${DEMO_DIR}/canon-demo.png"

echo "done:"
echo "  ${DEMO_DIR}/canon.wav"
echo "  ${DEMO_DIR}/canon-demo.mp4"
echo "  ${DEMO_DIR}/canon-demo.png"
