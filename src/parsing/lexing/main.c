/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:14:59 by jtoumani          #+#    #+#             */
/*   Updated: 2025/09/26 14:25:02 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "parser.h"
#include "debug.h"

char	*expand_or_not(char *seg_str, t_seg_type seg_type, t_env_list *envlst,
        int last_status, int i);
char	*segments_expand(t_segment_list *seglst, t_env_list *envlst, int last_status);

char	*expand_or_not(char *seg_str, t_seg_type seg_type, t_env_list *envlst,
        int last_status, int i);

extern char **environ;

static void print_words_and_segments(t_token_list *lst, t_env_list *envlst, int last_status)
{
    t_token         *tk;
    t_segment_list  segs;
    char            *expanded;

    tk = lst->head;
    while (tk)
    {
        if (tk->type == TK_WORD)
        {
            printf("WORD: \"%s\"\n", tk->value);
            init_segment_lst(&segs);
            if (find_segment(&segs, tk->value))
            {
                print_segment_list(&segs);
                expanded = segments_expand(&segs, envlst, last_status);
                printf("Expanded word: \"%s\"\n", expanded ? expanded : "(null)");
            }
        }
        tk = tk->next;
    }
}

int main(int argc, char **argv, char **envp)
{
    t_env_list   envlst;    // lokale Structs, keine Pointer
    t_token_list toklst;    // lokale Structs, keine Pointer
    char         *line;
    int          last_status;

    (void)argc; (void)argv;

    init_env_lst(&envlst);
    get_envs(envp, &envlst);
    last_status = 0;

    while ((line = readline("911TurboS> ")))
    {
        if (*line) add_history(line);

        int ret;

        init_token_lst(&toklst);
        ret = tokenize(&toklst, line);

        printf("%s\n", line);
        printf("tokenize() ret = %d\n", ret);

        printf("Tokens (before):\n");
        print_tokens(&toklst);

        print_words_and_segments(&toklst, &envlst, last_status);

        // Rufe final_token immer auf, damit du den Effekt siehst
        final_token(&toklst, &envlst, last_status);

        printf("Final tokens:\n");
        print_tokens(&toklst);

        free(line);
    }
    return 0;
}