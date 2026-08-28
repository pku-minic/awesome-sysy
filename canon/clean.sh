#!/usr/bin/env bash
set -euo pipefail

DEMO_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${DEMO_DIR}/build"

if [[ -d "${BUILD_DIR}" ]]; then
  rm -rf -- "${BUILD_DIR}"
fi

rm -f -- \
  "${DEMO_DIR}/canon.wav" \
  "${DEMO_DIR}/canon-demo.mp4" \
  "${DEMO_DIR}/canon-demo.png"
