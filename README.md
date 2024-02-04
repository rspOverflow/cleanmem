# libcleanmem
## A simple mark-and-sweep garbage collector

This is a simple heap mark-and-sweep garbage collector.

## Compile instructions

Dependencies: 

1. Any version of GCC that supports stdbool.h and stdint.h
2. stdio.h (Can be a partial implementation. printf and abort required.)
3. make
4. ar

To build, simply run make! The resulting library binaries should be in a 'build' folder. Meanwhile, just copy the header files to anywhere in your source tree as long as they are together in the same directory. Enjoy!

## Version

Version 0.0.1\
January 24, 2024

## License

**Until further notice, all commits before and after within this project is subject to the Mozilla Public License 2.0**\
**By using this library, you agree to this condition.**
