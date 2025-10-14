# Makefile for execution functions
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I../../../include -I../../../include/libft
SRC = exec_basics.c exec_basics1.c exec_builtins.c exec_builtins1.c exec_parent_runner.c exec_redirections.c exec_redirections1.c exec_utility_to_run.c \
	../../../Garbage_Collector/garbage_collector.c \
	../../../Garbage_Collector/garbage_collector1.c \
	../../../Garbage_Collector/garbage_collector_utils.c \
	../../../Garbage_Collector/garbage_collector_utils1.c \
	../../../main.c
OBJ = $(SRC:.c=.o)
NAME = execution_functions

all: $(NAME)

LIBFT = ../../../include/libft/libft.a
LIBFT_DIR = ../../../include/libft

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
