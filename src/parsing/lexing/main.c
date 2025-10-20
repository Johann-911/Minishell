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


extern char **environ;

/* Hilfs-Debug: env list ausgeben mit Adressen/Längen */
static void print_env_list_debug(t_env_list *lst)
{
    t_env_node *n;
    size_t idx = 0;

    if (!lst)
    {
        printf("env list: (null)\n");
        return;
    }
    printf("Env list (size=%zd):\n", lst->size);
    n = lst->head;
    while (n)
    {
        size_t klen = n->key ? ft_strlen(n->key) : 0;
        size_t vlen = n->value ? ft_strlen(n->value) : 0;
        printf("  [%02zu] key=\"%s\" (%p) len=%zu  value=\"%s\" (%p) len=%zu\n",
               idx++,
               n->key ? n->key : "(null)", (void*)n->key, klen,
               n->value ? n->value : "(null)", (void*)n->value, vlen);
        n = n->next;
    }
}

/* Kleiner Test-Driver: tokens + segment debug (wie vorher) */
static void test_input(char *line)
{
    if (!line)
        return;

    printf("%s\n", line);
    if (!check_tokens(line, 0))
    {
        printf("[ERR] %s\n", line);
        return;
    }
    printf("[OK] %s\n", line);

    t_token_list lst = {0};
    init_token_lst(&lst);
    if (!tokenize(&lst, line))
    {
        printf("tokenize failed\n");
        return;
    }

    print_tokens(&lst);

    /* Für jedes WORD Token: Segmente bauen und ausgeben */
    for (t_token *tok = lst.head; tok; tok = tok->next)
    {
        if (tok->type != TK_WORD)
            continue;
        t_segment_list segs = {0};
        init_segment_lst(&segs);
        if (!find_segment(&segs, tok->value))
        {
            printf("Segmentierung fehlgeschlagen für: \"%s\"\n", tok->value);
            continue;
        }
        printf("WORD: \"%s\"\n", tok->value);
        print_segment_list(&segs);
    }
}

int main(int argc, char **argv)
{
    t_env_list envlist;

    /* sichere Initialisierung der Liste bevor befüllt wird */
    envlist.head = envlist.tail = NULL;
    envlist.size = 0;

    /* get_envs ausführen und debug-print */
    if (!get_envs(environ, &envlist))
    {
        fprintf(stderr, "get_envs failed\n");
        return 1;
    }
    print_env_list_debug(&envlist);

    /* optional: falls Kommandozeilenargumente vorhanden, teste diese und exit */
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
            test_input(argv[i]);
        return 0;
    }

    /* REPL */
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

        test_input(line);
        free(line);
    }
    return 0;
}