##
## EPITECH PROJECT, 2025
## NTS_clone
## File description:
## Makefile
##

NAME = nanotekspice
TEST_NAME = unit_tests

TEST_DIR = tests
BUILD_DIR := build
SRC_DIR := src
COVERAGE_DIR := $(BUILD_DIR)/coverage
TEST_EXEC := $(BUILD_DIR)/$(TEST_NAME)


SRC 	= 		$(SRC_DIR)/Parser.cpp	\

MAIN 	= 		$(SRC_DIR)/main.cpp

TEST_SRC = test.cpp \


OBJ = $(SRC:.cpp=.o)
OBJ_MAIN = $(MAIN:.cpp=.o)

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -Iinclude -Itests
TEST_FLAGS = $(CXXFLAGS) -std=c++17 --coverage -lcriterion


all: $(NAME)

$(NAME): $(OBJ) $(OBJ_MAIN)
	$(CXX) $(OBJ) $(OBJ_MAIN) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build_test:
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(TEST_FLAGS) $(SRC) $(TEST_DIR)/$(TEST_SRC) -o $(TEST_EXEC)

clean:
	@rm -f $(OBJ)
	@rm -f $(OBJ_MAIN)
	@rm -f $(BUILD_DIR)/*.gcda
	@rm -f $(BUILD_DIR)/*.gcno

fclean: clean
	@rm -f $(NAME)
	@rm -f $(TESTNAME)
	@rm -rf $(BUILD_DIR)

re: fclean all

tests_run: clean build_test
	$(TEST_EXEC)

coverage:
	@mkdir -p $(COVERAGE_DIR)
	@$(TEST_EXEC)
	@gcovr -r . --exclude='tests/.*' --exclude='.*\.hpp'
	@gcovr -r . --exclude='tests/.*' --exclude='.*\.hpp' --txt-metric branch

.PHONY: all clean fclean re tests_run coverage
