# facebooc-q0

Assessing Your C Programming Skills

This lab will give you practice in the style of programming you will need to be able to do proficiently,
especially for the later assignments in the class. The material covered should all be review for you. Some
of the skills tested are:
* Explicit memory management, as required in C.
* Creating and manipulating pointer-based data structures.
* Working with strings.
* Enhancing the performance of key operations by storing redundant information in data structures.
* Implementing robust code that operates correctly with invalid arguments, including NULL pointers.
* Singly linked list and string sort implementation
* The sorting algorithm should be merge sort

The lab involves implementing a queue, supporting both last-in, first-out (LIFO) and first-in-first-out (FIFO)
queueing disciplines. The underlying data structure is a singly-linked list, enhanced to make some of the
operations more efficient.

## Prerequisites

There are a few prerequisites which must be installed on your machine before you will
be able to build and run the program.

The following command will install all required and optional dependencies on Ubuntu
Linux 18.04 or later:
```shell
$ sudo apt install build-essential git clang-format cppcheck aspell colordiff valgrind
```

Note: [Cppcheck](http://cppcheck.sourceforge.net/) version must be at least 1.90, otherwise
it might report errors with false positives. You can get its version by executing `$ cppcheck --version`.
Check [Developer Info](http://cppcheck.sourceforge.net/devinfo/) for building Cppcheck from source. Alternatively,
you can make use of [snap](https://snapcraft.io/) for latest Cppcheck:
```shell
$ sudo snap install cppcheck
$ export PATH=/snap/bin:$PATH
```

## Integrate clang-format to vim
If you want to run `clang-format` automatically after saving with vim, 
clang-format supports integration for vim according to [Clang 11 documentation](https://clang.llvm.org/docs/ClangFormat.html). 

By adding the following into `$HOME/.vimrc`
```shell
function! Formatonsave()
  let l:formatdiff = 1
  py3f <path to your clang-format.py>/clang-format.py
endfunction
autocmd BufWritePre *.h,*.hpp,*.c,*.cc,*.cpp call Formatonsave()
```
Note: on Ubuntu Linux 18.04, the path to `clang-format.py` is `/usr/share/vim/addons/syntax/`.  

## Running the autograders

compile your code to create the testing program `test`
```shell
$ make
```

Check the correctness of your code:
```shell
$ make test
```

Each step about command invocation will be shown accordingly.

Check the memory issue of your code:
```shell
$ make valgrind
```

## Files

You will handing in these two files
* queue.h : Modified version of declarations including new fields you want to introduce
* queue.c : Modified version of queue code to fix deficiencies of original code

Tools for evaluating your queue code
* Makefile : Builds the evaluation program `test`
* README.md : This file

Helper files
* test.c : Code for `test`

## License

`facebooc-q0`is released under the BSD 2 clause license. Use of this source code is governed by
a BSD-style license that can be found in the LICENSE file.

External source code:
* [git-good-commit](https://github.com/tommarshall/git-good-commit): MIT License

**This Program is rewritten from [sysprog21 /
lab0-c](https://github.com/sysprog21/lab0-c)**
