#!/usr/bin/env bash
# run_forever.sh
# Compile the toolchain (only if sources exist), then run runner in an infinite loop
# until a counterexample file is produced by runner.
#
# Usage: ./run_forever.sh [path-to-solution-binary-or-cmd]
# Example: ./run_forever.sh ./sol
#
# By default it uses ./sol as the solution. You can pass any command (with args) as $1.
# The script runs ./runner with --tests 1 repeatedly, incrementing the RNG seed each iteration.

set -euo pipefail

SOLUTION="${1:-./sol}"   # pass alternate solution (like "./my_solution")
INTERACTOR_SRC="./interactive/interactor.cpp"
RUNNER_SRC="./interactive/runner.cpp"
SOLUTION_SRC="./interactive/solve.cpp"  # optional compile if you want the example compiled

INTERACTOR_BIN="./interactor"
RUNNER_BIN="./runner"
SOLUTION_BIN="${SOLUTION}"

# Runner runtime settings
N=100          # range for hidden number (1..N); adjust to your problem
MAXQ=100       # max queries judge allows
TIMEOUT=1.5    # per-test timeout in seconds
LOGDIR="run_logs"
mkdir -p "$LOGDIR"

# Compile if source files exist and binaries missing or sources newer than binaries
compile_if_needed() {
    if [[ -f "$INTERACTOR_SRC" ]]; then
        if [[ ! -x "$INTERACTOR_BIN" || "$INTERACTOR_SRC" -nt "$INTERACTOR_BIN" ]]; then
        echo "Compiling $INTERACTOR_SRC -> $INTERACTOR_BIN"
        g++ -std=c++17 -O2 "$INTERACTOR_SRC" -o "$INTERACTOR_BIN" || { echo "interactor compile failed"; exit 2; }
        fi
    fi

    if [[ -f "$RUNNER_SRC" ]]; then
        if [[ ! -x "$RUNNER_BIN" || "$RUNNER_SRC" -nt "$RUNNER_BIN" ]]; then
            echo "Compiling $RUNNER_SRC -> $RUNNER_BIN"
            g++ -std=c++17 -O2 "$RUNNER_SRC" -o "$RUNNER_BIN" -pthread || { echo "runner compile failed"; exit 2; }
        fi
    fi

    # If the user asked to use the provided example solution, compile it
    if [[ "$SOLUTION_BIN" == "./sol" && -f "$SOLUTION_SRC" ]]; then
        if [[ ! -x "$SOLUTION_BIN" || "$SOLUTION_SRC" -nt "$SOLUTION_BIN" ]]; then
        echo "Compiling $SOLUTION_SRC -> $SOLUTION_BIN"
        g++ -std=c++17 -O2 "$SOLUTION_SRC" -o "$SOLUTION_BIN" || { echo "solution_example compile failed"; exit 2; }
        fi
    fi

    if [[ ! -x "$RUNNER_BIN" ]]; then
        echo "runner binary not found at $RUNNER_BIN. Please compile runner.cpp first."
        exit 2
    fi
    if [[ ! -x "$INTERACTOR_BIN" ]]; then
        echo "interactor binary not found at $INTERACTOR_BIN. Please compile interactor.cpp first."
        exit 2
    fi
    if [[ ! -x "$SOLUTION_BIN" ]]; then
        echo "solution binary not found at $SOLUTION_BIN. Provide path as first arg or compile your solution."
        exit 2
    fi
}

compile_if_needed

SEED=0
ITER=0

echo "Starting infinite test loop. Logs written to $LOGDIR. Press Ctrl+C to stop."
while true; do
    ITER=$((ITER+1))
    SEED=$((SEED+1))
    TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
    OUTFILE="${LOGDIR}/runner_${TIMESTAMP}_iter${ITER}_seed${SEED}.log"
    echo "[$(date +'%F %T')] Iteration #$ITER  seed=$SEED  (log: $OUTFILE)"
    # Run runner for a single random test (runner will write counterexample_*.log on failure and exit)
    # We pass --seed to help reproducibility; the runner will pick a hidden randomly if different
    "$RUNNER_BIN" --solution "$SOLUTION_BIN" --tests 1 --N "$N" --maxq "$MAXQ" --timeout "$TIMEOUT" --seed "$SEED" \
        > "$OUTFILE" 2>&1 || true

    # Check for counterexample files produced by the runner
    CE_FILE=$(ls counterexample_*.log 2>/dev/null | head -n 1 || true)
    if [[ -n "$CE_FILE" ]]; then
        echo "==== FAILURE FOUND! ===="
        echo "Counterexample file: $CE_FILE"
        echo "Dumping counterexample contents:"
        echo "---------------------------"
        sed -n '1,200p' "$CE_FILE"
        echo "---------------------------"
        echo "Full runner log: $OUTFILE"
        exit 0
    fi

    # Optional: rotate logs or keep only last X logs to save space
    # keep last 500 logs
    ls -1t "${LOGDIR}/runner_"* 2>/dev/null | tail -n +501 | xargs -r rm --

    # small sleep to avoid busy looping (adjust as needed)
    sleep 0.05
done
