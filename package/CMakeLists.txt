cmake_minimum_required(VERSION 3.13)
project(
    SSGifier
    LANGUAGES
        CXX)
set(CMAKE_CXX_STANDARD 17)
SET (PROJECT_ROOT "${PROJECT_SOURCE_DIR}")
SET (CMAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/src")
set (SOURCE_FILES ${CMAKE_DIRECTORY}/main.cpp ${CMAKE_DIRECTORY}/Utils.cpp ${CMAKE_DIRECTORY}/ArgumentQueue.cpp ${CMAKE_DIRECTORY}/FileProcessor.cpp ${CMAKE_DIRECTORY}/MessagePrinter.cpp)
add_executable(SSGifier ${SOURCE_FILES})
set(OUTPUT_NAME SSGifier.exe)
set_target_properties(
    PROPERTIES 
        OUTPUT_NAME "SSGifier"

)
