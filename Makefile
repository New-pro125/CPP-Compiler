CXX :=g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wno-unused-function -I./src -I./build

all: cmake-build

cmake-build:
	 cmake -S . -B build
	 cmake --build build

run:
	./build/compiler $(filter-out $@,$(MAKECMDGOALS))

%:
	@:

clean:
	rm -rf build
.PHONY: all cmake-build clean
