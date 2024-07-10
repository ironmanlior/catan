CXX = g++

# Compiler flags
CXXFLAGS = -g -Wall
# Linker flags

# Source files for the main application
MAIN_SRCS = main.cpp edge.cpp catan.cpp board.cpp player.cpp place.cpp road.cpp

# Source files for the tests
TEST_SRCS = test.cpp edge.cpp catan.cpp board.cpp player.cpp place.cpp road.cpp

# Object files for the main application
MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)

# Object files for the tests
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Executable name for the main application
EXEC = catan

# Test executable name
TEST_EXEC = test_catan

# Valgrind options
VALGRIND_OPTS = --leak-check=full --show-leak-kinds=all

all: $(EXEC)

$(EXEC): $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(MAIN_OBJS)

test: $(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $(TEST_OBJS)
	./$(TEST_EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o $(EXEC) $(TEST_EXEC)