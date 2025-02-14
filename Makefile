##
## EPITECH PROJECT, 2025
## NTS_clone
## File description:
## Makefile
##

NAME = nanotekspice

SRC = main.cpp

OBJ = $(SRC:.cpp=.o)

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f unit_tests

re: fclean all

tests_run:
	$(CXX) $(CXXFLAGS) tests/test.cpp -o unit_tests
	./unit_tests

.PHONY: all clean fclean re test
