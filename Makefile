NAME        := minishell
PARSER_BIN  := parse_test

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g
INC_DIRS    := include include/libft
INCS        := $(addprefix -I, $(INC_DIRS))

LIBFT_DIR   := include/libft
LIBFT       := $(LIBFT_DIR)/libft.a

LDFLAGS     := -L$(LIBFT_DIR) -lft -lreadline -lncurses

OBJ_DIR     := _obj
RM          := rm -rf

# Quellen
MINI_SRCS := \
    src/execution/main.c \
    src/execution/redirections.c \
	Garbage_Collector/garbage_collector.c \
    src/parsing/token_check.c \
    src/parsing/token_utils.c \
    src/parsing/token_to_cmd.c \
    src/parsing/debug.c

PARSER_SRCS := \
    src/parsing/main.c \
    src/parsing/token_check.c \
    src/parsing/token_utils.c \
    src/parsing/token_to_cmd.c \
    src/parsing/debug.c \
    src/parsing/test_stubs.c

# Objekte
MINI_OBJS   := $(MINI_SRCS:%.c=$(OBJ_DIR)/%.o)
PARSER_OBJS := $(PARSER_SRCS:%.c=$(OBJ_DIR)/%.o)

# Default
all: $(NAME)

# Binaries
$(NAME): $(LIBFT) $(MINI_OBJS)
	@$(CC) $(CFLAGS) $(MINI_OBJS) -o $@ $(LDFLAGS)

$(PARSER_BIN): $(LIBFT) $(PARSER_OBJS)
	@$(CC) $(CFLAGS) $(PARSER_OBJS) -o $@ $(LDFLAGS)

# Libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Compile rule
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME) $(PARSER_BIN)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re $(PARSER_BIN)