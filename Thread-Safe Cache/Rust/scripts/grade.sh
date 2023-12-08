#!/usr/bin/env bash
# set -e
set -uo pipefail
IFS=$'\n\t'

# Imports library.
BASEDIR=$(dirname "$0")
source $BASEDIR/grade-utils.sh

run_linters || exit 1

RUNNERS=(
    "cargo"
    "cargo --release"
    "cargo_asan"
    "cargo_asan --release"
    "cargo_tsan"
    "cargo_tsan --release"
)


test_failed=false

# Executes test for each runner.
for RUNNER in "${RUNNERS[@]}"; do
    echo "Running with $RUNNER..."

    if [ "$test_failed" = false ]; then
        echo "    Testing cache.rs..."
        if [ $(run_tests) -ne 0 ]; then
            test_failed=true
        fi
    fi
done

if [ "$test_failed" = false ]; then
    echo "Tests failed."
else
    echo "Tests passed."
fi
