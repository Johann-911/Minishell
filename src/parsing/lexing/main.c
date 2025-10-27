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
static void test_input(char *s)
{
    int ok = check_tokens(s, 0);
    printf("[%s] %s\n", ok ? "OK" : "ERR", s);
    if (!ok) return;

    t_token_list lst = (t_token_list){0};
    if (tokenize(&lst, s)) {
        print_tokens(&lst);

        // Segmente pro WORD-Token anzeigen
        for (t_token *t = lst.head; t; t = t->next) {
            if (t->type != TK_WORD) continue;
            t_segment_list segs;
            init_segment_lst(&segs);
            if (find_segment(&segs, t->value)) {
                printf("WORD: \"%s\"\n", t->value);
                print_segment_list(&segs);
            } else {
                printf("Segmentierung fehlgeschlagen für: \"%s\"\n", t->value);
            }
        }
    }
}

int main(int argc, char **argv)
{
    if (argc > 1) {
        for (int i = 1; i < argc; i++)
            test_input(argv[i]);
        return 0;
    }

    while (1) {
        char *line = readline("911TurboS> ");
        if (!line) {           // CTRL-D
            printf("exit\n");
            break;
        }
        if (*line)             // nicht-leere Eingaben in History
            add_history(line);

        test_input(line);
        free(line);
    }
    return 0;
}