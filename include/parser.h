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
// #include "executor.h"

#include <aio.h>
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
	TK_BUILTIN, // 1xxe
	S_QUOTES,   // 2 ''
	D_QUOTES,   // 3 ""
	TK_INFILE,  // 4 <
	TK_OUTFILE, // 5 >
	TK_HEREDOC, // 6 <<
	TK_APPEND,  // 7 >>
	TK_PIPE,    // 8 |
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
bool						is_valid_red(char *str, int *i);
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
// token to command
int find_segment(t_segment_list *lst, char *str);
// static int quote_segment(t_segment_list *lst, char *str, int *i);
// static int no_quote_segment(t_segment_list *lst, char *str, int *i);
char	*segments_expand(t_segment_list *seglst, t_env_list *envlst,
		int last_status);
int push_segment(t_segment_list *lst, t_segment *segment);
t_segment *create_segment(char *start, int len, t_seg_type type);
void	final_token(t_token_list *toklst, t_env_list *envlst, int last_status);
char	*look_for_cmd(t_token *token, t_token_list *toklst, t_cmd_list *cmdlst);
char	**create_array(t_token *token, t_cmd_node *cmdnode, int i);
int	count_args(t_token *token);
bool	is_redirection(t_toktype t);
bool is_built_in(char *str);
int collect_redirs(t_token *token, t_cmd_node *cmdnode);

//create
t_cmd_node	*create_cmdnode(void);
void create_filenode(char *str, int red_type, t_file_list *filelst);
void	push_cmd(t_cmd_list *lst, t_cmd_node *node);
void	push_file(t_file_list *lst, t_file_node *node);

//env node adding and lst adding
int find_key(char *str, t_env_node *env);
int find_value(char *str, t_env_node *env);
int push_env(t_env_list *lst, t_env_node *env);
int get_envs(char **env, t_env_list *lst);
char	*expand_env(char *str, t_env_list *env_lst);
char *get_expand(char *seg_str, int i, int last_status, t_env_list *envlst);


//initializing
void init_env_lst(t_env_list *lst);
void	init_token_lst(t_token_list *lst);
void init_segment_lst(t_segment_list *lst);
//debug
void    *gc_malloc(size_t size);
char    *gc_substr(char *s, unsigned int start, size_t len);
void print_tokens(const t_token_list *lst);
void print_segment_list(const t_segment_list *list);
void init_segment_lst(t_segment_list *lst);
void print_env_list_debug(t_env_list *lst);
char	*gc_strdup(const char *s);
char	*gc_strndup(const char *s, size_t n);
char	**gc_split(const char *s, char c);
char	*gc_strjoin(const char *s1, const char *s2);
char	*gc_itoa(int n);




#endif
