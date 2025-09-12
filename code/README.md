# README

This is the file structure of the project:

```bash
.
├── src
│  ├── checks.hpp
│  ├── is_substr.cpp
│  ├── longest_common_substring.cpp
│  ├── longest_palindrome_substr.cpp
│  └── main.cpp
├── .gitignore
├── gen_tests.sh
├── Makefile
├── README.md
└── test.py
build/main
```

The code can be compiled via:

```bash
$ make # outputs binary to build/main
```

The program reads this files on it's execution:

```bash
transmission1.txt
transmission2.txt
mcode1.txt
mcode2.txt
mcode3.txt
```

The program recieves a path to a directory as it's first argument, if none is
provided, the program defaults it to the current working dir.

```bash
$ make run args="dir"
# optionally via:
# $ ./build/main <dir>
```

We also include the `gen_tests.sh` and `test.py` scripts, which correspondingly
configure the following test suite, and execute the test suite:

```bash
tests
├── case01_generic_pal_and_match
├── case02_generic_common_block
├── case03_generic_empty_vs_nonempty
├── edge01_even_vs_odd_pal
├── edge02_no_common_substr
└── edge03_multi_hits_overlap
```

Each directory contains the specified files, plus an `expected.txt`. To run every the entire
tests suite automatically, simply execute:

```bash
$ make test
[PASS] case01_generic_pal_and_match
[PASS] case02_generic_common_block
[PASS] case03_generic_empty_vs_nonempty
[PASS] edge01_even_vs_odd_pal
[PASS] edge02_no_common_substr
[PASS] edge03_multi_hits_overlap

=== All Passed ===
```
