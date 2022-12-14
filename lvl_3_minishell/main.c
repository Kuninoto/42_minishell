/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:02:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/14 00:36:59 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Returns true if it has sucessfully executed an implemented command or printed an env variable
bool	cmd_check(t_statement *statement, char **envp)
{
	if (ft_strncmp(statement->cmd, "cd\0", 3) == 0)
		cmd_cd(statement->args[1]);
	else if (ft_strncmp(statement->cmd, "echo\0", 5) == 0)
		cmd_echo(statement);
	else if (ft_strncmp(statement->cmd, "pwd\0", 4) == 0)
		cmd_pwd();
	else if (ft_strncmp(statement->cmd, "env\0", 4) == 0)
		cmd_env(envp);
	else if (ft_strncmp(statement->cmd, "$", 1) == 0)
		print_env_variables(&statement->cmd[1]);
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
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	// CTRL+C
	sigaction(SIGINT, &sa, NULL);
	// Ignore CTRL+backslash
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_statement	*statement_list;
	t_statement *temp;

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
		free(input);
	/* 	for (t_statement *temp = statement_list; temp != NULL; temp = temp->next)
		{
			printf("COMMAND: %s\n", temp->cmd);
			printf("ARGS: ");
			for (size_t i = 0; temp->args[i] != NULL; i++)
				printf("%s ", temp->args[i]);
			if (temp->operator)
				printf("\nOPERATOR: %d\n", temp->operator);
			printf("\n");
		}
		printf("\n"); */

		temp = statement_list;
		while (temp != NULL)
		{
			// cd must be applied without forking
			if (cmd_check(temp, envp) == false)
			{	
				if (fork() == 0)
				{
					if (cmd_binaries(temp, envp) == true)
						exit(EXIT_SUCCESS);
				}
				else
					wait(NULL);
			}
			temp = temp->next;
		}
		lstclear(&statement_list);
	}
	return (EXIT_SUCCESS);
}
