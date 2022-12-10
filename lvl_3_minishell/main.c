/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:02:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/10 20:25:35 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	cmd_check(char **inputs)
{
	if (ft_strncmp(inputs[0], "echo", ft_strlen(inputs[0])))
	{
		cmd_echo(inputs);
	}
}

int	main(void)
{
	char	*input;
	char	**inputs;
//	char	*binary_path;
//	char	*args[] = {"", NULL};
//	char 	*envp[] = {"", NULL};

	welcome_art();
//	envp[0] = join_freev2("PATH:", getenv("PATH"));
	while (1)
	{
		input = readline("$ ");
		inputs = parse_input(input);
		cmd_check(inputs);
		/* binary_path = ft_strjoin("/usr/bin/", input);
		if (fork() == 0)
		{
			args[0] = binary_path;
			if (execve(binary_path, args, envp) == -1)
				printf("%s: command not found\n", input);
		}
		wait(NULL); */
		free(input);
		free_matrix(inputs);
		//free(binary_path);
	}
	return (EXIT_SUCCESS);
}