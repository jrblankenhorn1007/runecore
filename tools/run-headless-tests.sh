#!/bin/sh

set -u

script_dir=$(CDPATH= cd "$(dirname "$0")" && pwd) || {
    printf '%s\n' 'Unable to locate the repository root.' >&2
    exit 1
}
repo_root=$(CDPATH= cd "$script_dir/.." && pwd) || {
    printf '%s\n' 'Unable to locate the repository root.' >&2
    exit 1
}

build_dir="$repo_root/build"
log_file="$build_dir/headless-tests.log"
status_file="$build_dir/headless-tests.status"

if ! mkdir -p "$build_dir"; then
    printf 'Unable to create build directory: %s\n' "$build_dir" >&2
    exit 1
fi

if ! printf '%s\n' 'RUNNING' > "$status_file"; then
    printf 'Unable to write test status file: %s\n' "$status_file" >&2
    exit 1
fi

if ! : > "$log_file"; then
    if ! printf '%s\n' \
        'EXIT_CODE=1' \
        'ERROR=Unable to prepare the CTest log file' \
        "LOG_FILE=$log_file" > "$status_file"; then
        printf 'Unable to write test status file: %s\n' "$status_file" >&2
    fi
    printf 'Unable to prepare CTest log file: %s\n' "$log_file" >&2
    exit 1
fi

if ctest --test-dir "$build_dir" --output-on-failure "$@" > "$log_file" 2>&1; then
    exit_code=0
else
    exit_code=$?
fi

if ! {
    printf 'EXIT_CODE=%s\n' "$exit_code"
    printf 'LOG_FILE=%s\n' "$log_file"
} > "$status_file"; then
    printf 'CTest exited with %s, but status could not be written to %s\n' \
        "$exit_code" "$status_file" >&2
    exit 1
fi

if [ "$exit_code" -ne 0 ]; then
    printf 'Headless CTest failed with exit code %s; see %s\n' \
        "$exit_code" "$log_file" >&2
fi

exit "$exit_code"
