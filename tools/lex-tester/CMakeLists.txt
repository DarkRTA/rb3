cmake_minimum_required(VERSION 3.15)

project(DataFlexTester LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

add_executable(DataFlexTester
    "main.cpp"
    "../../src/system/obj/DataFlex.c"
    "../../src/system/obj/DataFlex_target.cpp"
    "../../src/system/obj/DataFlex.h"
    "../../src/system/obj/DataFlex_target.h"
    "../../src/system/obj/DataFile_Flex.h"
)

target_include_directories(DataFlexTester
    PUBLIC
    "."
    "../../src/system/obj"
)

target_compile_definitions(DataFlexTester
    PUBLIC
    "DATAFLEX_TESTER"
)
