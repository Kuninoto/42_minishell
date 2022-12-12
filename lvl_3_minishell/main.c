/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:02:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/12 02:15:28 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Returns true if it has sucessfully executed an implemented command or printed an env variable
bool	cmd_check(char **inputs, char **envp)
{
	if (ft_strncmp(inputs[0], "cd\0", 3) == 0)
		cmd_cd(inputs[1]);
	else if (ft_strncmp(inputs[0], "echo\0", 5) == 0)
		cmd_echo(inputs);
	else if (ft_strncmp(inputs[0], "pwd\0", 4) == 0)
		cmd_pwd();
	else if (ft_strncmp(inputs[0], "env\0", 4) == 0)
		cmd_env(envp);
	else if (ft_strncmp(inputs[0], "$", 1) == 0)
		print_env_variables(&inputs[0][1]);
	else
		return (false);
	return (true);
}

void	dismiss_signal(int signum)
{
	if (signum == SIGINT)
		write(STDOUT_FILENO, "\n$ ", 3);
}

void	config_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &dismiss_signal;
	// CTRL+C
	//! Not working properly. CTRL+C then UP arrow (or any other key) prints another prompt
	//! cat without arguments than CTRL+C also not working
	//! Not interrupting '2nd dimension' processes, i.e a.out's are not being closed by CTRL+C
	sigaction(SIGINT, &sa, NULL);
	// Ignore CTRL+backslash
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**inputs;
	pid_t	child_pid;

	(void)argc;
	(void)argv;

	config_signals();
	welcome_art();
	while (1)
	{
		input = readline("$ ");
		// CTRL + D
		if (input == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			exit(EXIT_SUCCESS);
		}
		if (input[0] == '\0')
			continue;
		add_history(input);
		if (ft_strncmp(input, "exit\0", 5) == 0)
		{
			rl_clear_history();
			exit(EXIT_SUCCESS);
		}
		// exit must be applied without forking
		inputs = parse_input(input);
		free(input);
		// cd must be applied without forking
		if (cmd_check(inputs, envp) == false)
		{	
			child_pid = fork();
			if (child_pid == 0)
			{
				if (cmd_binaries(inputs, envp) == true)
					kill(child_pid, SIGKILL);
			}
			else
				wait(NULL);
		}
		free_matrix(inputs);
	}
	return (EXIT_SUCCESS);
}
