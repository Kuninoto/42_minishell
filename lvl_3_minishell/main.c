/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:02:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/15 19:11:28 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Returns true if it has sucessfully executed an implemented command or printed an env variable
bool	cmd_check(t_statement *statement, char **envp)
{
	if (streq(statement->argv[0], "echo"))
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
			
		// left side
		if (fork() == 0)
		{
			close(STDOUT_FILENO); // fd 1
			dup(pipedes[1]);	// fd output
			close(pipedes[0]);
    		close(pipedes[1]);
			exec_cmd(current_node, envp);
		}
		// right side
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
		if (cmd_check(current_node, envp))
			return ;
		cmd_binaries(current_node, envp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (current_node->operator == REDIRECT_OUTPUT_REPLACE)
		{
			current_node->operator = NONE;
			if (fork() == 0)
			{
				write(1, "ola", 3);
				close(STDOUT_FILENO); // 1
				printf("%d", open(current_node->next->argv[0], O_CREAT | O_TRUNC));
				close(1);
				//cmd_binaries(current_node, envp);
				exit(EXIT_SUCCESS);
			}
			wait(NULL);
		}
	} 
	exit(EXIT_SUCCESS);
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
		
		/* for (t_statement *temp = statement_list; temp != NULL; temp = temp->next)
		{
			printf("ARGC: %d\n", temp->argc);
			printf("ARGV: ");
			for (size_t i = 0; temp->argv[i] != NULL; i++)
				printf("%s ", temp->argv[i]);
			printf("\nOPERATOR: %d\n", temp->operator);
			printf("\n");
		}
		printf("\n"); */	


		// cd is not working because it must be applied without forking
		if (lstsize(statement_list) == 1)
		{
			if (streq(statement_list->argv[0], "cd"))
				cmd_cd(statement_list->argv[1]);
			else if (fork() == 0)
			{		
				exec_cmd(statement_list, envp);
			//	exit(EXIT_SUCCESS);
			}
			wait(NULL);
		}
		else
		{
			if (fork() == 0)
				exec_cmd(statement_list, envp);
			wait(NULL);
		}
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
