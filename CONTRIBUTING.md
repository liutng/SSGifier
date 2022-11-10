Everyone is welcomed to contribute. Want to contribute to SSGifier? You need to know a few things down below.

# Requirements

Before submitting your code, you need to test your work throughly and make sure your code has passed all Unit Tests to ensure it will not break anything that already exists in the code, to run the Unit Test please refer to the section of `Unit Test ` in this document. This project strives to make the code as clean as possible, please format and lint your code before making any submission as well.

After you added features in your code, please don't forget to write Unit Tests to test the function you wrote, Unit Testing is an affective way to make sure your code is designed well and will not be affected by corner cases. This project uses Catch as the C++ Unit Test framework, check [Catch Document](https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md#top) for documentations.

# Envrionment

- C++ 2017
- Linux/Windows
- LLVM for Clang++

# How to compile

with GCC: `g++ -std=c++17 main.cpp Utils.cpp ArgumentQueue.cpp FileProcessor.cpp MessagePrinter.cpp `
with clang++: `clang++ -std=c++17 main.cpp Utils.cpp ArgumentQueue.cpp FileProcessor.cpp MessagePrinter.cpp `

# Visual Studio Code Integration

Clang-tidy and Clang-format is bundled with C++ extension plugin on Visual Studio Code. To use them, please follow steps as follows:

## Clang-tidy

- Install **C++ extension plugin** from `Extensions` tab in Visual Studio Code .
- Open `action search` by pressing `Ctrl+Shift+P` and type `Run Code Analysis` to search the action of `clang-tidy `.
- Select `C/C++:Run Code Analysis on All Files` and wait for the checking process to finish.
- select **PROBLEMS** tab on the bottom panel to check the suggested problem by clang-tidy.

## Clang-format

- Install **C++ extension plugin** from `Extensions` tab in Visual Studio Code.
- Format document with VS Code's default formatter(`Ctrl + Alt + L` by default) and .clang-format will be used as the guideline of the formatter.

## Unit Test

- Depending on the OS, run `test.bat` on Windows, or run `test.sh` on Linux in the terminal to compile and run the Test Units.
- Add new unit test functions to `test/unit_tests.cpp` for creating new Unit Tests
- For how to use the unit testing framework, check this [Catch Document](https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md#top)
- A test report file `test_result.xml` will also be generated to the root of the project when the unit test is sucessfully conducted.
