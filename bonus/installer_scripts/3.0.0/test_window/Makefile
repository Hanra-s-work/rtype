##
## EPITECH PROJECT, 2024
## rtype
## File description:
## Makefile
##

# Compiler and flags
CXX = g++

# compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra

# Library flags
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Project name
NAME = my_window

# Source and object files
SRC = src/main.cpp
OBJ = $(SRC:.cpp=.o)

# Default rule
all: $(NAME)

# Create the executable
$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

# Compile the project in debug mode
debug: CXXFLAGS += -g

# Clean object files
clean:
	rm -f $(OBJ)

# Clean object files and executable
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
