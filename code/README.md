# README

This is the file structure of the project:

```bash
.
├── src
│  └── main.cpp
├── .gitignore
├── Makefile
└── README.md
build/main
```

The code can be compiled via:

```bash
$ make # outputs binary to build/main
```

The program receives a path to a dimacs as it's first argument.

```bash
$ make run args="path"
# optionally via:
# $ ./build/main <path>
```
