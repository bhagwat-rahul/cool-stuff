#!/usr/bin/env bash
set -euo pipefail

# Download dimacs cnf files from .uri into a test-data folder wherever this bash is
SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
DATA_DIR="$SCRIPT_DIR/test-data"

mkdir -p "$DATA_DIR"

wget -c --content-disposition -P "$DATA_DIR" -i "$SCRIPT_DIR/track_main_2026.uri"

# Decompress all .xz files and remove the .xz archives
shopt -s nullglob
xz_files=("$DATA_DIR"/*.xz)
if (( ${#xz_files[@]} > 0 )); then
    xz -d -T0 "${xz_files[@]}"
fi
