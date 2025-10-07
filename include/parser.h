/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:40:09 by jtoumani          #+#    #+#             */
/*   Updated: 2025/09/25 18:58:41 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// Includes -- BEGIN
#include "minishell.h"
# include <stdio.h>
#include "parser.h"
// #include "executor.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>

// Includes -- END

// Structs -- BEGIN
typedef struct s_file_node	t_file_node;
typedef struct s_file_list	t_file_list;
typedef struct s_cmd_node	t_cmd_node;
typedef struct s_cmd_list	t_cmd_list;
typedef struct s_env_node	t_env_node;
typedef struct s_env_list	t_env_list;

typedef enum e_toktype
{
	TK_WORD,    // 0
	TK_BUILTIN, // 1
	S_QUOTES,   // 2 ''
	D_QUOTES,   // 3 ""
	TK_INFILE,  // 4 <
	TK_OUTFILE, // 5 >
	TK_HEREDOC, // 6 <<
	TK_APPEND,  // 7 >>
	TK_PIPE,    // 8 |
	// TK_AMPERSAND, //9 &
	// TK_AND, //10 &&
	// TK_OR, //11 ||
}							t_toktype;

typedef enum seg_type
{
	SEG_NO_QUOTE,
	SEG_SINGLE,
	SEG_DOUBLE,
}							t_seg_type;

typedef struct s_segment
{
	char					*value;
	t_seg_type				type;
	struct s_segment		*next;
}							t_segment;

typedef struct s_segment_list
{
	t_segment				*head;
	t_segment				*tail;
	ssize_t					size;
}							t_segment_list;

typedef struct s_token
{
	t_toktype				type;
	char					*value;
	t_segment_list			*segment_list;
	struct s_token			*next;
}							t_token;

typedef struct s_token_list
{
	int						syntax_error;
	t_token					*head;
	t_token					*tail;
	ssize_t					size;
	char					*input;
}							t_token_list;
// Structs -- END

// Lexing checking syntax
// int							main(int argc, char **argv);
bool						is_valid_red(char *str, int i);
bool						is_red(char *str, int *i);
bool						is_valid_pipe(char *str, int *i);
bool						check_tokens(char *str, int i);
bool						is_boundary_char(char c);
bool						we_have_token(const char *str, int *i);
int							scan_quote(const char *str, int i);
bool						is_valid_quote(char *str, int *i);
int							skip_spaces(char *str, int i);
//tokenize 
t_token *create_token(t_toktype type, char *val);
int	push_token(t_token_list *lst, t_token *token);
int	add_token(t_token_list *lst, t_toktype type, char *str, int len);
int	handle_word(t_token_list *lst, char *input, int *i);
int	tokenize(t_token_list *lst, char *input);
int	red_len(char *input, int i);
t_toktype red_type(const char *str, int i);
int handle_quote(char *input, int *i);
int handle_redir(t_token_list *lst, char *input, int *i, int red_len);
int	word_end(char *input, int i);

//debug
void    *gc_malloc(size_t size);
char    *gc_substr(char *s, unsigned int start, size_t len);
void print_tokens(const t_token_list *lst);



#endif
