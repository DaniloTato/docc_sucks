#!/usr/bin/env python3

import sys
import subprocess
from pathlib import Path
import difflib


def run_case(bin_path: Path, case_dir: Path) -> bool:
    case_arg = str(case_dir.resolve()) + "/"

    try:
        result = subprocess.run(
            [str(bin_path), case_arg],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            check=False,
        )
    except FileNotFoundError:
        print(f"[ERROR] Binary not found: {bin_path}")
        return False

    output_txt = case_dir / "output.txt"
    output_txt.write_text(result.stdout, encoding="utf-8")

    expected_file = case_dir / "expected.txt"
    if not expected_file.exists():
        print(f"[WARN] No expected.txt in {case_dir.name}; marking as FAIL.")
        return False

    expected = expected_file.read_text(encoding="utf-8")
    actual = result.stdout

    if expected == actual:
        print(f"[PASS] {case_dir.name}")
        return True

    print(f"[FAIL] {case_dir.name}")
    print("  --- Diff (expected vs output) ---")
    for line in difflib.unified_diff(
        expected.splitlines(keepends=True),
        actual.splitlines(keepends=True),
        fromfile="expected.txt",
        tofile="output.txt",
    ):
        sys.stdout.write(line)
    print("  --- stderr ---")
    sys.stdout.write(result.stderr)
    return False


def main():
    if len(sys.argv) != 2:
        print("Usage: python3 scripts/run_all_tests.py <path_to_binary>")
        sys.exit(2)

    bin_path = Path(sys.argv[1])
    tests_root = Path("tests")
    if not tests_root.exists():
        print("[ERROR] tests/ directory not found.")
        sys.exit(2)

    cases = sorted([p for p in tests_root.iterdir() if p.is_dir()])
    if not cases:
        print("[ERROR] No test case folders in tests/.")
        sys.exit(2)

    for case_dir in cases:
        if not run_case(bin_path, case_dir):
            sys.exit(1)

    print("\n=== All Passed ===")


if __name__ == "__main__":
    main()
