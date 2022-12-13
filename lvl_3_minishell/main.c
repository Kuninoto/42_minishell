/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:02:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/13 19:17:23 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Returns true if it has sucessfully executed an implemented command or printed an env variable
bool	cmd_check(char **parsed, char **envp)
{
	if (ft_strncmp(parsed[0], "cd\0", 3) == 0)
		cmd_cd(parsed[1]);
	else if (ft_strncmp(parsed[0], "echo\0", 5) == 0)
		cmd_echo(parsed);
	else if (ft_strncmp(parsed[0], "pwd\0", 4) == 0)
		cmd_pwd();
	else if (ft_strncmp(parsed[0], "env\0", 4) == 0)
		cmd_env(envp);
	else if (ft_strncmp(parsed[0], "$", 1) == 0)
		print_env_variables(&parsed[0][1]);
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
	char		*input;
	t_statement	*statement_list;

	(void)argc;
	(void)argv;
	(void)envp;
	config_signals();
	welcome_art();
	while (1)
	{
		input = readline("$ ");
		// CTRL+D
		if (input == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			exit(EXIT_SUCCESS);
		}
		if (input[0] == '\0')
			continue;
		add_history(input);
		// exit must be applied without forking
		if (ft_strncmp(input, "exit\0", 5) == 0)
		{
			rl_clear_history();
			exit(EXIT_SUCCESS);
		}
		statement_list = parse_input(input);
		for (t_statement *temp = statement_list; temp != NULL; temp = temp->next)
			printf("%s -> ", temp->command);
		printf("\n");
		free(input);
		/* // cd must be applied without forking
		if (cmd_check(parsed, envp) == false)
		{	
			if (fork() == 0)
			{
				if (cmd_binaries(parsed, envp) == true)
					exit(EXIT_SUCCESS);
			}
			else
				wait(NULL);
		}
		free_matrix(parsed); */
	}
	return (EXIT_SUCCESS);
}
