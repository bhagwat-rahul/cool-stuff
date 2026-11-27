#!/usr/bin/env bash
set -euo pipefail

# Usage: ./download.sh <number_of_files> <zip|unzip>

[[ $# -eq 2 ]] || { echo "Usage: $0 <count> <zip|unzip>"; exit 1; }
[[ "$1" =~ ^[1-9][0-9]*$ ]] || { echo "Invalid file count"; exit 1; }
[[ "$2" == "zip" || "$2" == "unzip" ]] || { echo "Mode must be zip or unzip"; exit 1; }

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
DATA_DIR="$SCRIPT_DIR/test-data"
mkdir -p "$DATA_DIR"

head -n "$1" "$SCRIPT_DIR/track_main_2026.uri" |
    wget -c --content-disposition -P "$DATA_DIR" -i -

if [[ "$2" == "unzip" ]]; then
    shopt -s nullglob
    for f in "$DATA_DIR"/*.xz; do xz -d -T0 "$f"; done
    for f in "$DATA_DIR"/*.zip; do unzip -oq "$f" -d "$DATA_DIR" && rm "$f"; done
fi

echo "Done: $DATA_DIR"
