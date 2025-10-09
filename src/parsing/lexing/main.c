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
#include "parser.h"
#include "debug.h"

static void test_input(char *s)
{
    int ok = check_tokens(s, 0);
    printf("[%s] %s\n", ok ? "OK" : "ERR", s);
    if (!ok) return;

    t_token_list lst = (t_token_list){0};
    if (tokenize(&lst, s))
        print_tokens(&lst);
}

int main(int argc, char **argv)
{
    if (argc > 1) {
        for (int i = 1; i < argc; i++)
            test_input(argv[i]);
        return 0;
    }
    char buf[1024];
    while (fgets(buf, sizeof(buf), stdin)) {
        size_t n = strcspn(buf, "\n");
        buf[n] = '\0';
        test_input(buf);
    }
    return 0;
}


// static char	*read_line(const char *prompt)
// {
// 	char	buf[256];
// 	char	*line;
// 	size_t	len;
// 	ssize_t	r;
// 	size_t	i;
// 	char	*n;

// 	write(STDOUT_FILENO, prompt, strlen(prompt));
// 	line = NULL;
// 	len = 0;
// 	while (1)
// 	{
// 		r = read(STDIN_FILENO, buf, sizeof(buf));
// 		if (r <= 0)
// 		{
// 			if (len == 0)
// 				return (free(line), NULL);
// 			return (line);
// 		}
// 		i = 0;
// 		while (i < (size_t)r)
// 		{
// 			if (buf[i] == '\n')
// 				return (line);
// 			n = malloc(len + 2);
// 			if (!n)
// 				return (free(line), NULL);
// 			if (line)
// 			{
// 				memcpy(n, line, len);
// 				free(line);
// 			}
// 			n[len] = buf[i];
// 			n[len + 1] = '\0';
// 			line = n;
// 			len++;
// 			i++;
// 		}
// 	}
// }
