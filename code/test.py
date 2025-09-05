#!/usr/bin/env python3

"""
Generate edge-case inputs for your C++ program and run them all.

Usage:
  python3 scripts/gen_and_run_tests.py [--exe ./bin/prog] [--tests-dir tests] [--no-fuzz]

What it does:
  - Creates multiple test case directories under tests/
  - Each case has: transmission1.txt, transmission2.txt, mcode1.txt..mcode3.txt
  - Runs the program as: <exe> <testcase_dir> and writes stdout to output.txt, stderr to error.txt
  - Non-zero exit codes are recorded in results summary

Notes:
  - We DO NOT assert correctness here (format/indices in your program can vary).
    This harness is for coverage/regression. If you later want oracle checks, you
    can extend `expected_output_*` helpers accordingly.
"""

import argparse
import os
import shutil
import string
import subprocess
import sys
from pathlib import Path
from random import randint, choice, seed

seed(12345)  # reproducible fuzz

# --------------------------- Helpers ---------------------------


def write_case(dirpath: Path, t1: str, t2: str, m1: str, m2: str, m3: str):
    dirpath.mkdir(parents=True, exist_ok=True)
    (dirpath / "transmission1.txt").write_text(t1, encoding="utf-8")
    (dirpath / "transmission2.txt").write_text(t2, encoding="utf-8")
    (dirpath / "mcode1.txt").write_text(m1, encoding="utf-8")
    (dirpath / "mcode2.txt").write_text(m2, encoding="utf-8")
    (dirpath / "mcode3.txt").write_text(m3, encoding="utf-8")


def rand_str(alpha: str, n: int) -> str:
    return "".join(choice(alpha) for _ in range(n))


def make_palindrome(core: str, even=True) -> str:
    if even:
        return core + core[::-1]
    else:
        # put a middle char to ensure odd length
        mid = core[-1] if core else "x"
        return core + mid + core[::-1]


def run_case(exe: str, case_dir: Path):
    out_path = case_dir / "output.txt"
    err_path = case_dir / "error.txt"
    with (
        out_path.open("w", encoding="utf-8") as out,
        err_path.open("w", encoding="utf-8") as err,
    ):
        proc = subprocess.run(
            [exe, str(case_dir) + ("" if str(case_dir).endswith("/") else "/")],
            stdout=out,
            stderr=err,
            text=True,
        )
        return proc.returncode


# --------------------------- Edge Cases ---------------------------


def build_cases(root: Path, include_fuzz=True):
    if root.exists():
        # keep existing outputs but remove previous input files to ensure freshness
        # (delete directories to be clean)
        shutil.rmtree(root)
    root.mkdir(parents=True, exist_ok=True)

    cases = []

    # 01: Empty transmissions
    cases.append(("case01_empty_trans", "", "", "A", "", "XYZ"))

    # 02: Single character transmissions
    cases.append(("case02_single_char", "A", "B", "A", "B", "C"))

    # 03: All same char transmissions
    cases.append(("case03_all_same", "aaaaaa", "aaaa", "a", "aa", "aaa"))

    # 04: Palindrome mixed in the middle, and overlapping mcodes
    t1 = "abcxyzyxdef"  # has odd palindrome "xyzyx"
    t2 = "zzxyzyxzz"  # shares substring "xyzyx"
    cases.append(("case04_pal_mix", t1, t2, "xy", "yzy", "xyzyx"))

    # 05: Disjoint alphabets (no common substrings > 1 char)
    cases.append(("case05_disjoint", "abcdef", "UVWXYZ", "gh", "ab", "XY"))

    # 06: Palindromes at edges + repeated patterns
    t1 = "abbaZZZZ"  # even palindrome at start
    t2 = "YYYYracecar"  # odd palindrome at end
    cases.append(("case06_edges", t1, t2, "abba", "ZZ", "racecar"))

    # 07: Empty mcodes (edge: empty pattern)
    #   Depending on your is_substr semantics, empty pattern might be found at 0 or be invalid.
    #   Harness just runs; you can inspect outputs.
    cases.append(("case07_empty_mcodes", "content", "another", "", "", ""))

    # 08: Repeated pattern stress
    t1 = "abcabcabcabc"
    t2 = "zzabcabczz"
    cases.append(("case08_repeat_pat", t1, t2, "abcabc", "bcab", "cabcab"))

    # 09: Mixed lengths & symbols
    t1 = "A1!A2@A3#A4$A5%"
    t2 = "zzA3#A4$yy"
    cases.append(("case09_mixed_len", t1, t2, "A3#", "A4$", "A2@A3#"))

    # 10: Even-only palindromes in transmission
    t1 = "xxabbaqq"
    t2 = "abba"
    cases.append(("case10_even_only", t1, t2, "abba", "bb", "xq"))

    # Optional fuzz: random small alphabets with guaranteed palindromes inside
    if include_fuzz:
        alpha = "abcd"
        for i in range(1, 6):
            core = rand_str(alpha, randint(2, 5))
            pal_even = make_palindrome(core, even=True)
            pal_odd = make_palindrome(core, even=False)
            t1 = rand_str(alpha, 5) + pal_even + rand_str(alpha, 4)
            t2 = rand_str(alpha, 3) + pal_odd + rand_str(alpha, 6)
            m1 = core[: max(1, len(core) // 2)]
            m2 = pal_even[: min(6, len(pal_even))]
            m3 = rand_str(alpha, 3)
            cases.append((f"fuzz{i:02d}", t1, t2, m1, m2, m3))

    # Write all cases
    for name, t1, t2, m1, m2, m3 in cases:
        case_dir = root / name
        write_case(case_dir, t1, t2, m1, m2, m3)

    return [root / name for name, *_ in cases]


# --------------------------- Main ---------------------------


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument(
        "--exe",
        default="./bin/prog",
        help="Path to the compiled C++ executable (default: ./bin/prog)",
    )
    ap.add_argument(
        "--tests-dir",
        default="tests",
        help="Directory to create test cases under (default: tests)",
    )
    ap.add_argument("--no-fuzz", action="store_true", help="Skip generating fuzz cases")
    args = ap.parse_args()

    exe = args.exe
    tests_root = Path(args.tests_dir)

    cases = build_cases(tests_root, include_fuzz=not args.no_fuzz)

    print("=== Running test cases ===")
    failures = 0
    for case_dir in cases:
        print(f"Running {case_dir.name} ...", end="", flush=True)
        rc = run_case(exe, case_dir)
        if rc == 0:
            print(" OK")
        else:
            print(f" FAIL (exit={rc})")
            failures += 1

    print("\n=== Summary ===")
    print(f"Total cases: {len(cases)}")
    print(f"Failures:    {failures}")
    sys.exit(1 if failures else 0)


if __name__ == "__main__":
    main()
