CXX :=g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wno-unused-function -I./src -I./build

all: cmake-build

cmake-build:
	 cmake -S . -B build
	 cmake --build build

# TODO: add run command into make file

clean: 
	rm -rf build
.PHONY: all cmake-build clean