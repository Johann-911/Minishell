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
#include "minishell.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void	test_input(char *s)
{
	int	ok;

	ok = check_tokens(s, 0);
	printf("[%-3s] %s\n", ok ? "OK" : "ERR", s);
}

int	main(int argc, char **argv)
{
	char	*line;
	size_t	len;
	ssize_t	r;

	line = NULL;
	len = 0;
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
			test_input(argv[i]);
		return (0);
	}
	printf("Syntax-Test (CTRL+D beendet)\n");
	while (1)
	{
		printf("Zoro > ");
		fflush(stdout);
		r = getline(&line, &len, stdin);
		if (r < 0)
			break ;
		if (r > 0 && line[r - 1] == '\n')
			line[r - 1] = '\0';
		if (*line == '\0')
			continue ;
		test_input(line);
	}
	free(line);
	return (0);
}
