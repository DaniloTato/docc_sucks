# README

This is the file structure of the project:

```bash
.
├──├── src
│  ├── knapsack.cpp
│  ├── knapsack.hpp
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

The program reads from stdin in this format:

```
N number of items
N values...
N weights...
W capacity
```

The program receives a path to a directory as it's first argument, if none is
provided, the program defaults it to the current working dir.

```bash
$ make run args="< input.txt"
# optionally via:
# $ ./build/main < input.txt
```

We also include the `gen_tests.sh` and `test.py` scripts, which correspondingly
configure the following test suite, and execute the test suite:

```bash
tests
├── case01_basic_example
├── case02_single_item_fits
├── case03_single_item_no_fit
├── case04_all_items_fit
├── case05_zero_capacity
├── case06_no_items
├── case07_same_weights
└── case08_larger_example
```

Each directory contains the specified files, plus an `expected.txt`. To run every the entire
tests suite automatically, simply execute:

```bash
$ make test
[PASS] case01_basic_example
[PASS] case02_single_item_fits
[PASS] case03_single_item_no_fit
[PASS] case04_all_items_fit
[PASS] case05_zero_capacity
[PASS] case06_no_items
[PASS] case07_same_weights
[PASS] case08_larger_example

=== All Passed ===
```
