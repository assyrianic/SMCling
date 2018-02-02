# .SMExtension.SMCling
SourceMod extension that embeds the Cling C++ interpreter to run C++ source code as plugins.

## Building
To build SMCling, you need to [build the Cling interpreter first](https://root.cern.ch/cling-build-instructions)

Cling is built atop Clang and LLVM, so you'll need the header files for both systems to compile Cling AND to use Cling in the extension.

after you've built Cling from scratch using the build instructions, copy the "lib" folder from the "inst" or "obj" folder into the smcling directory. The "lib" folder is required as it contains the libraries needed to link the extension.

Next, create a folder in "lib" and name it "include", then copy the header files (clang, clang-c, cling, llvm, llvm-c) to the "include" folder in "lib".

After that, you can now compile smcling!
