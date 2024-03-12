# Project name
NAME = fdf

# Compilator
CC = cc
# Compilator flags
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

# Headers
HEADERS = includes/fdf.h

# Source directory
SRCS_DIR = utilities/
# Objects directory
OBJS_DIR = objects/

# Source file names
SRCS_NAME = main.c \

# Objects file names
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS_NAME:.c=.o)

# Compilation process
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

# Remaking
re: clean all

# PHONY files
.PHONY: all clean fclean re
