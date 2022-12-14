/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:02:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/14 23:14:06 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Returns true if it has sucessfully executed an implemented command or printed an env variable
bool	cmd_check(t_statement *statement, char **envp)
{
	if (streq(statement->argv[0], "cd"))
		cmd_cd(statement->argv[1]);
	else if (streq(statement->argv[0], "echo"))
		cmd_echo(statement);
	else if (streq(statement->argv[0], "pwd"))
		cmd_pwd();
	else if (streq(statement->argv[0], "env"))
		cmd_env(envp);
	else if (statement->argv[0][0] ==  '$')
		print_env_variables(&statement->argv[0][1]);
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

void	exec_cmd(t_statement *current_node, char **envp)
{
	int	pipedes[2];
	//	bytes written on pipedes[1] can be read on pipedes[0]
	//ls -a | wc -l 
	if (current_node->operator == PIPE)
	{
		current_node->operator = NONE;
		if (pipe(pipedes) == -1)
			panic("Failed to pipe");
			
		// right side
		if (fork() == 0)
		{
			close(STDOUT_FILENO); // fd 1
			dup(pipedes[1]);	// fd output
			close(pipedes[0]);
    		close(pipedes[1]);
			exec_cmd(current_node, envp);
		}
		
		// left side
		if (fork() == 0)
		{
			close(STDIN_FILENO); // fd 0
			dup(pipedes[0]);	// input
			close(pipedes[0]);
    		close(pipedes[1]);
			exec_cmd(current_node->next, envp);
		}
		close(pipedes[0]);
    	close(pipedes[1]);
		wait(NULL);
		wait(NULL);
	}	
	else if (current_node->operator == NONE)
	{
		if (cmd_check(current_node, envp) == false)
		{
			cmd_binaries(current_node, envp);
			exit(EXIT_SUCCESS);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_statement	*statement_list;

	(void)argc;
	(void)argv;
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
		if (streq(input, "exit"))
		{
			rl_clear_history();
			exit(EXIT_SUCCESS);
		}
		statement_list = parse_input(input);
		free(input);
		for (t_statement *temp = statement_list; temp != NULL; temp = temp->next)
		{
			printf("ARGV: ");
			for (size_t i = 0; temp->argv[i] != NULL; i++)
				printf("%s ", temp->argv[i]);
			printf("\nOPERATOR: %d\n", temp->operator);
			printf("\n");
		}
		printf("\n");
		if (lstsize(statement_list) == 1)
		{
			if (fork() == 0)
			{		
				exec_cmd(statement_list, envp);
				exit(EXIT_SUCCESS);
			}
			wait(NULL);
		}
		else
			exec_cmd(statement_list, envp);

		/* 
		temp = statement_list;
		while (temp != NULL)
		{
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
		*/
		lstclear(&statement_list);
	}
	return (EXIT_SUCCESS);
}
