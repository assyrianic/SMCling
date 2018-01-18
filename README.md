# .SMExtension.SMCling
SourceMod extension that embeds the Cling C++ interpreter to run C++ source code as plugins.

## Building
To build SMCling, you need to [build the Cling interpreter first](https://root.cern.ch/cling-build-instructions)

After you've successfully built the Cling C++ interpreter from scratch, you must either dynamically link your extension with libcling.so OR link your extension with the static library "libclingInterpreter.a" and its dependencies.

Please know that Cling is built atop Clang and LLVM, so you'll need the header files for both systems to compile Cling AND to use Cling in the extension.
