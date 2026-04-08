cmake_minimum_required(VERSION 3.16)
project(cpp_compiler)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

FLEX_TARGET(Lexer src/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
BISON_TARGET(Parser src/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h)
ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)
set(
    COMPILER_CORE_SOURCES
    ${FLEX_Lexer_OUTPUTS}
    ${BISON_Parser_OUTPUTS}
    src/compiler.cpp
    src/quadruple_generator.cpp
    src/error_handler.cpp
)


add_executable(
    compiler
    ${COMPILER_CORE_SOURCES}
    src/main.cpp
)
target_include_directories(compiler PRIVATE src ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(compiler PRIVATE -Wall -Wextra -Wno-unused-function)
