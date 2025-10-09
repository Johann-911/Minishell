/* debug.h - Add this to your project */
#ifndef DEBUG_H
# define DEBUG_H

# include <stdio.h>
# include "parser.h"

# define COLOR_GREEN  "\x1b[32m"
# define COLOR_YELLOW "\x1b[33m"
# define COLOR_RESET  "\x1b[0m"

void print_tokens(const t_token_list *list);

#endif

// /* If command types aren't defined in minishell.h, define them here */
// # ifndef CMD
// enum cmd_types {
//     CMD = 1,
//     PIPE,
//     BUILTIN
// };
// # endif

/* Debug macros */
# if CURRENT_DEBUG_LEVEL >= DBG_LEVEL_ERROR
#  define DEBUG_ERROR(fmt, ...) fprintf(stderr, COLOR_RED "[ERROR] " COLOR_RESET fmt "\n", ##__VA_ARGS__)
# else
#  define DEBUG_ERROR(fmt, ...)
# endif

# if CURRENT_DEBUG_LEVEL >= DBG_LEVEL_WARN
#  define DEBUG_WARN(fmt, ...) fprintf(stderr, COLOR_YELLOW "[WARN] " COLOR_RESET fmt "\n", ##__VA_ARGS__)
# else
#  define DEBUG_WARN(fmt, ...)
# endif

# if CURRENT_DEBUG_LEVEL >= DBG_LEVEL_INFO
#  define DEBUG_INFO(fmt, ...) fprintf(stderr, COLOR_BLUE "[INFO] " COLOR_RESET fmt "\n", ##__VA_ARGS__)
# else
#  define DEBUG_INFO(fmt, ...)
# endif

# if CURRENT_DEBUG_LEVEL >= DBG_LEVEL_TRACE
#  define DEBUG_TRACE(fmt, ...) fprintf(stderr, COLOR_CYAN "[TRACE] " COLOR_RESET fmt "\n", ##__VA_ARGS__)
# else
#  define DEBUG_TRACE(fmt, ...)
# endif

/* Function prototypes */
// void validate_cmd_list(t_cmd_list *cmd_list);
// void print_cmd_list(t_cmd_list *cmd_list);
// void print_tokens(t_token_list *list);

