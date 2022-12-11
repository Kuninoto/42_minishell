/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:02:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/11 18:50:15 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	cmd_check(char **inputs)
{
	if (ft_strncmp(inputs[0], "echo\0", 5) == 0)
		cmd_echo(inputs);
	else if (ft_strncmp(inputs[0], "pwd\0", 4) == 0)
		cmd_pwd();
	else
		cmd_binaries(inputs);
}

int	main(void)
{
	char	*input;
	char	**inputs;

	welcome_art();
	while (1)
	{
		input = readline("$ ");
		inputs = parse_input(input);
		if (fork() == 0)
		{
			cmd_check(inputs);
		}
		wait(NULL);
		free(input);
		free_matrix(inputs);
	}
	return (EXIT_SUCCESS);
}