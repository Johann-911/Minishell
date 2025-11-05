NAME        := minishell
PARSER_BIN  := parse_test

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g
INC_DIRS    := include include/libft
INCS        := $(addprefix -I, $(INC_DIRS))

LIBFT_DIR   := include/libft
LIBFT       := $(LIBFT_DIR)/libft.a
LDFLAGS     := -L$(LIBFT_DIR) -lft
RL_LIBS     := -lreadline -lncurses

OBJ_DIR     := _obj
RM          := rm -rf

# Verwende '>' als Rezept-Prefix statt TAB
.RECIPEPREFIX := >

# Nur fürs Hauptprojekt (unverändert, kannst du später pflegen)
MINI_SRCS := \
    src/parsing/lexing/main.c \
    src/parsing/lexing/token_check.c \
    src/parsing/lexing/token_utils.c \
    src/parsing/lexing/tokenize.c \
    src/parsing/lexing/tokenize_helper.c \
    src/parsing/lexing/debug.c \
    src/parsing/lexing/test_subs.c \
    src/parsing/command/find_token.c \
    src/parsing/command/token_to_cmd.c \
    src/parsing/command/token_to_cmd_helper.c

# Parse-Test: nur Lexing-Dateien (ohne token_to_cmd)
PARSER_SRCS := \
    src/parsing/lexing/main.c \
    src/parsing/lexing/token_check.c \
    src/parsing/lexing/token_utils.c \
    src/parsing/lexing/tokenize.c \
    src/parsing/lexing/tokenize_helper.c \
    src/parsing/lexing/debug.c \
    src/parsing/lexing/init.c \
    src/parsing/command/find_token.c \
    src/parsing/command/token_to_cmd.c \
    src/parsing/command/token_to_cmd_helper.c \
    src/parsing/command/add_env.c \
    src/parsing/command/cmdlst_filelst.c \
    src/parsing/command/expand_env.c \
    src/parsing/lexing/gc_substr_shim.c

#         Garbage_Collector/garbage_collector1.c \
#     Garbage_Collector/garbage_collector_utils.c

MINI_OBJS   := $(MINI_SRCS:%.c=$(OBJ_DIR)/%.o)
PARSER_OBJS := $(PARSER_SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MINI_OBJS)
>@$(CC) $(CFLAGS) $(MINI_OBJS) -o $@ $(LDFLAGS)

$(PARSER_BIN): $(LIBFT) $(PARSER_OBJS)
>$(CC) $(CFLAGS) $(PARSER_OBJS) -o $@ $(LDFLAGS) $(RL_LIBS)

$(LIBFT):
>@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c
>@mkdir -p $(@D)
>@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
>@$(RM) -r $(OBJ_DIR)
>@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
>@$(RM) $(NAME) $(PARSER_BIN)
>@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re $(PARSER_BIN)