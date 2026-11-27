#!/usr/bin/env bash
set -euo pipefail

# Download all 2026 main track dimacs cnf files into a test-data/ folder wherever this bash script is located
SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
DATA_DIR="$SCRIPT_DIR/test-data"

mkdir -p "$DATA_DIR"

wget -c --content-disposition -P "$DATA_DIR" -i "$SCRIPT_DIR/track_main_2026.uri"
