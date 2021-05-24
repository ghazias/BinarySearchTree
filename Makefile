CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -g -std=c++17
LINK.o = $(LINK.cc)
TEST_OBJS = test_main.o test_bst.o

all: test_main bst_example

test_main: $(TEST_OBJS)

bst_example: bst_example.o

clean:
	rm -f *.o test_main bst_example
