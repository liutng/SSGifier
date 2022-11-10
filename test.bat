clang++ -std=c++17 ./test/unit_tests.cpp Utils.cpp ArgumentQueue.cpp MessagePrinter.cpp FileProcessor.cpp ./test/catch_amalgamated.cpp -o test.exe
test.exe --reporter xml::out=test_result.xml --reporter console::out=-::colour-mode=ansi
@echo off
del test.exe
