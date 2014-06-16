INCLUDE=$(shell pwd)
TEST_SRC=$(shell find . -name '*.cpp')

CXX=clang++
CXXFLAGS=-Wall -std=c++11 -I$(INCLUDE) -lgtest

EXEC=build/test

all:: test

test::
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(TEST_SRC)
	@./build/test

clean::
	$(RM) -rf build/*
