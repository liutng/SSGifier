Everyone is welcomed to contribute. Want to contribute to SSGifier? You need to know a few things down below.

# Requirements

- C++ 2017
- Linux/Windows
- LLVM for Clang++

# How to compile

`g++ -std=c++17 main.cpp ArgumentQueue.cpp FileProcessor.cpp MessagePrinter.cpp `

# Visual Studio Code Integration

Clang-tidy and Clang-format is bundled with C++ extension plugin on Visual Studio Code. To use them, please follow steps as follows:

## Clang-tidy

- Install **C++ extension plugin** from `Extensions` tab in Visual Studio Code .
- Open action search by pressing `Ctrl+Shift+P` and type `Run Code Analysis` to search the action of `clang-tidy `.
- Select `C/C++:Run Code Analysis on All Files` and wait for the checking process to be done.
- select **PROBLEMS** tab on the bottom panel to check the suggested problem by clang-tidy.

## Clang-format

- Install **C++ extension plugin** from `Extensions` tab in Visual Studio Code.
- Format document with VS Code's default formatter(`Ctrl + Alt + L` by default) and .clang-format will be used as the guideline of the formatter.
