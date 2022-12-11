/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:02:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/11 20:37:36 by nnuno-ca         ###   ########.fr       */
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
		// cd must be applied without forking
		if (ft_strncmp(inputs[0], "cd\0", 3) == 0)
			cmd_cd(inputs[1]);
		else if (fork() == SUCESS)
			cmd_check(inputs);
		wait(NULL);
		free(input);
		free_matrix(inputs);
	}
	return (EXIT_SUCCESS);
}