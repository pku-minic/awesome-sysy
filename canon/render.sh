#!/usr/bin/env bash
set -euo pipefail

DEMO_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${DEMO_DIR}/build"
INPUT_PATH="${1:-${DEMO_DIR}/canon.mml}"
OUTPUT_PATH="${2:-${BUILD_DIR}/score.wav}"
COMPILER_INPUT="${SYSY_COMPILER:-}"
CONTAINER_IMAGE="${SYSY_COMPILER_DEV_IMAGE:-maxxing/compiler-dev}"

if [[ -z "${COMPILER_INPUT}" || ! -x "${COMPILER_INPUT}" ]]; then
  echo "usage: SYSY_COMPILER=/absolute/path/to/compiler ./render.sh [score.mml|score.mid] [output.wav]" >&2
  exit 2
fi
if [[ ! -f "${INPUT_PATH}" ]]; then
  echo "error: score input does not exist: ${INPUT_PATH}" >&2
  exit 2
fi

for tool in docker; do
  if ! command -v "${tool}" >/dev/null 2>&1; then
    echo "error: required tool not found: ${tool}" >&2
    exit 2
  fi
done

mkdir -p "${BUILD_DIR}" "$(dirname -- "${OUTPUT_PATH}")"

"${COMPILER_INPUT}" -riscv "${DEMO_DIR}/score2wav.c" -o "${BUILD_DIR}/score2wav.S"
docker run --rm \
  --user "$(id -u):$(id -g)" \
  -v "${DEMO_DIR}:/work" \
  -w /work \
  "${CONTAINER_IMAGE}" \
  sh -lc '
    clang build/score2wav.S -c -o build/score2wav.o \
      -target riscv32-unknown-linux-elf -march=rv32im -mabi=ilp32 &&
    ld.lld build/score2wav.o -L/opt/lib/riscv32 -lsysy \
      -o build/score2wav-riscv
  '
docker run --rm -i \
  --user "$(id -u):$(id -g)" \
  -v "${DEMO_DIR}:/work" \
  -w /work \
  "${CONTAINER_IMAGE}" \
  qemu-riscv32-static build/score2wav-riscv \
  < "${INPUT_PATH}" \
  > "${OUTPUT_PATH}"

echo "done: ${OUTPUT_PATH}"
