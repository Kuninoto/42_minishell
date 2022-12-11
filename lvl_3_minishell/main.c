/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:02:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/11 23:03:35 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	cmd_check(char **inputs)
{
	if (ft_strncmp(inputs[0], "cd\0", 3) == 0)
		cmd_cd(inputs[1]);
	else if (ft_strncmp(inputs[0], "echo\0", 5) == 0)
		cmd_echo(inputs);
	else if (ft_strncmp(inputs[0], "pwd\0", 4) == 0)
		cmd_pwd();
	else
		return (false);
	return (true);
}

void	dismiss_signal(int signum)
{
	if (signum == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	if (signum == SIGQUIT)
		exit(EXIT_SUCCESS);
}

void	config_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &dismiss_signal;
	// CTRL+C
	//! Completely fucked up
	sigaction(SIGINT, &sa, NULL);
	// CTRL+D
	//! Segfaulting
	sigaction(SIGQUIT, &sa, NULL);
}

int	main(void)
{
	char	*input;
	char	**inputs;
	pid_t	child_pid;

// TODO
//	config_signals();
	welcome_art();
	printf("MINISHELL pid = %d\n", getpid());
	while (1)
	{
		input = readline("$ ");
		if (ft_strncmp(input, "exit\0", 5) == 0)
			exit(EXIT_SUCCESS);
		// exit must be applied without forking
		inputs = parse_input(input);
		// cd must be applied without forking
		if (cmd_check(inputs) == false)
		{	
			child_pid = fork();
			if (child_pid == 0)
			{
				cmd_binaries(inputs);
				kill(child_pid, SIGKILL);
			}
			else
				wait(NULL);
		}
		free(input);
		free_matrix(inputs);
	}
	return (EXIT_SUCCESS);
}
