#!/usr/bin/env bash
set -e

# Compile generator, solution, brute (optional), and checker
g++ -std=c++17 -O2 contest/gen.cpp    -o gen
g++ -std=c++17 -O2 contest/sol.cpp    -o sol
# optional, if you want to keep a brute solution too
g++ -std=c++17 -O2 contest/brute.cpp  -o brute
# checker verifies output validity
g++ -std=c++17 -O2 contest/check.cpp  -o check

echo "Stress testing with validator (check)... Ctrl+C to stop"

while true; do
    ./gen > in.txt
    ./sol < in.txt > out.txt

    # Run checker with input and solution output
    ./check in.txt out.txt

    if [ $? -eq 0 ]; then
    printf "."
    else
        echo -e "\n❌ WRONG OUTPUT!"
        echo "--- Input ---"; cat in.txt
        echo "--- Output ---"; cat out.txt
        exit 1
    fi
done
