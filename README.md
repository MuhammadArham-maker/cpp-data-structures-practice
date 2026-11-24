# C++ Data Structures Practice

This repository contains four C++ console programs I wrote while practising the data-structure topics from my second semester.

The programs are separate exercises. They are not parts of one combined application, and each source file has its own `main()` function.

## Contents

| Folder | File | What I practised |
|---|---|---|
| `arrays/` | `Array.cpp` | Array operations such as finding extrema, reversing and rotating elements, finding duplicates, merging sorted arrays, and the two-sum problem |
| `linked-lists/` | `Linked_List.cpp` | Singly linked lists, doubly linked lists, and circular linked lists |
| `stacks/` | `Stack.cpp` | Array-based and linked-list stacks, balanced brackets, infix-to-postfix conversion, and postfix evaluation |
| `queues/` | `Queue.cpp` | Circular queues, linked-list queues, stack/queue conversions, queue reversal, and a deque |

## Compile and run

Compile one file at a time with a C++ compiler. For example:

```bash
g++ -std=c++17 arrays/Array.cpp -o arrays-program
./arrays-program
```

Use the corresponding source-file path for the other programs. On Windows, the generated executable can be run from the terminal with its `.exe` name.

## About this repository

These are learning and practice implementations. The aim is to keep the code I wrote organised and make it easier to revisit, run, and improve. The repository is a record of practice, rather than a production-ready data-structures library.
