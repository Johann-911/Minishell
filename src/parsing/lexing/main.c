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


static void	test_input(char *line, t_env_list *envlist, int last_status)
{
    t_token_list	lst;
    t_token			*tok;
    t_segment_list	segs;
    t_segment		*seg;
    char			*expanded;

    if (!line)
        return;
    printf("%s\n", line);
    if (!check_tokens(line, 0))
    {
        printf("[ERR] %s\n", line);
        return;
    }
    printf("[OK] %s\n", line);
    init_token_lst(&lst);
    if (!tokenize(&lst, line))
    {
        printf("tokenize failed\n");
        return;
    }
    print_tokens(&lst);
    tok = lst.head;
    while (tok)
    {
        if (tok->type == TK_WORD)
        {
            init_segment_lst(&segs);
            if (!find_segment(&segs, tok->value))
            {
                printf("Segmentierung fehlgeschlagen für: \"%s\"\n", tok->value);
                tok = tok->next;
                continue;
            }
            printf("WORD: \"%s\"\n", tok->value);
            print_segment_list(&segs);
            /* Expansion pro Segment (ohne segments_expand) */
            seg = segs.head;
            while (seg)
            {
                expanded = expand_or_not(seg->value, seg->type, envlist, last_status, 0);
                printf("Expanded seg: \"%s\"\n", expanded ? expanded : "(null)");
                seg = seg->next;
            }
        }
        tok = tok->next;
    }
}

int	main(int argc, char **argv)
{
    t_env_list	envlist;
    int			last_status;

    last_status = 0;
    if (!get_envs(environ, &envlist))
    {
        fprintf(stderr, "get_envs failed\n");
        return (1);
    }
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
            test_input(argv[i], &envlist, last_status);
        return (0);
    }
    while (1)
    {
        char *line = readline("911TurboS> ");
        if (!line)
        {
            printf("exit\n");
            break;
        }
        if (*line)
            add_history(line);
        test_input(line, &envlist, last_status);
        free(line);
    }
    return (0);
}