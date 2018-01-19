# .SMExtension.SMCling
SourceMod extension that embeds the Cling C++ interpreter to run C++ source code as plugins.

## Building
To build SMCling, you need to [build the Cling interpreter first](https://root.cern.ch/cling-build-instructions)

Cling is built atop Clang and LLVM, so you'll need the header files for both systems to compile Cling AND to use Cling in the extension.

The folders containing the header files (clang, clang-c, cling, llvm, llvm-c) should be in the same directory as "extension.cpp".

after you've built Cling from scratch using the build instructions, copy the "lib" folder from the "inst" folder into the same directory. The "lib" folder is required as it contains the static library to be linked to the extension.
