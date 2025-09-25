/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:14:59 by jtoumani          #+#    #+#             */
/*   Updated: 2025/09/25 18:55:52 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	main(int argc, char **argv, char **env)

{



	from_executor();


	from_parser();


	printf("This is a test from main\n");


	printf("This is a test from main\n");


	printf("This is a test from main\n");


	char	*test_str;





	(void)argc;


	(void)argv;


	(void)env;


	gc_init();


	while (1)


	{


		test_str = readline("Kayne West 🐐 > ");


		if (test_str)


		{


			if (ft_strncmp(test_str, "exit", 4) == 0)


			{


				free(test_str);


				break ;


			}


			printf("prompt : %s\n", test_str);


			free(test_str);


		}


	}


	clean_up();

	return (0);

}






