#!/usr/bin/env bash
set -euo pipefail

# singlesol.sh - stress helper that saves check stdout and ASan logs separately.
# Usage: ./singlesol.sh

# detect OS to decide whether to compile with sanitizers.
OS="$(uname -s 2>/dev/null || echo WIN)"

SANFLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer -g"
if [[ "$OS" == "MINGW"* || "$OS" == "CYGWIN"* || "$OS" == "WIN"* || "$OS" == "MSYS"* ]]; then
    echo "Detected Windows/MinGW environment ($OS). Compiling WITHOUT sanitizers."
    SANFLAGS=""
else
    echo "Detected $OS. Compiling WITH sanitizers."
fi

# compile executables (adjust file paths if your files are elsewhere)
echo "Compiling..."
g++ -std=c++17 -O2 $SANFLAGS contest/gen.cpp  -o gen
g++ -std=c++17 -O2 $SANFLAGS contest/solve.cpp  -o solve
# g++ -std=c++17 -O2 contest/brute.cpp -o brute
g++ -std=c++17 -O2 $SANFLAGS contest/check.cpp  -o check

echo "Compilation done."

# run pipeline: generate input, run solver, run checker
echo "Generating input..."
./gen > nvalues.txt

echo "Running solver..."
./solve < nvalues.txt > output.txt

echo "Running checker (stdout -> suminvalid.txt, stderr -> check_asan.log)..."
# Redirect stdout of check to suminvalid.txt and stderr (ASan/UBSan) to check_asan.log.
# Use '|| true' to avoid script exiting when check returns non-zero (set -e is enabled).
./check < output.txt > suminvalid.txt 2> check_asan.log || true

echo "Done."
echo
echo "Files produced:"
ls -l nvalues.txt output.txt suminvalid.txt check_asan.log || true

echo
echo "Show first 200 lines of check stderr (ASan/UBSan) if any:"
sed -n '1,200p' check_asan.log || true

echo
echo "Show first 200 lines of check stdout (suminvalid.txt):"
sed -n '1,200p' suminvalid.txt || true

# If you want to keep looping for continuous stress testing, uncomment below:
# while true; do
#     ./gen > nvalues.txt
#     ./solve < nvalues.txt > output.txt
#     ./check < output.txt > suminvalid.txt 2> check_asan.log || true
#     sleep 0.1
# done
