/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:02:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/20 18:34:37 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

void	exec_pipe(t_statement *node, char **envp)
{
	pid_t mshell_pid;
	int	pipedes[2];
	int	status;

	node->operator = NONE;
	if (pipe(pipedes) == -1)
		panic("Failed to pipe");
	// left side
	mshell_pid = fork();
	if (mshell_pid == 0)
	{
		close(STDOUT_FILENO); // fd 1
		dup(pipedes[1]);	// fd output
		close(pipedes[0]);
		close(pipedes[1]);
		exec_cmd(node, envp);
	}
	mshell_pid = fork();
	// right side
	if (mshell_pid == 0)
	{
		close(STDIN_FILENO); // fd 0
		dup(pipedes[0]);	// input
		close(pipedes[0]);
		close(pipedes[1]);
		exec_cmd(node->next, envp);
	}
	close(pipedes[0]);
	close(pipedes[1]);
	waitpid(mshell_pid, &status, 0);
	waitpid(mshell_pid, &status, 0);
	printf("EXIT STATUS OF CHILD = %d\n", WEXITSTATUS(status));
}

void	exec_cmd(t_statement *current_node, char **envp)
{
	//	bytes written on pipedes[1] can be read on pipedes[0]
	//ls -a | wc -l
	if (current_node->operator == PIPE)
		exec_pipe(current_node, envp);
	else if (current_node->operator == NONE)
	{
		if (cmd_check(current_node, envp))
			return ;
		cmd_binaries(current_node, envp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (current_node->operator == RDR_INPUT)
		{
			close(STDIN_FILENO); // 0
			open(current_node->next->argv[0], O_RDONLY);
		}
		else
		{
			close(STDOUT_FILENO); // 1
			if (current_node->operator == RDR_OUT_APPEND)
				open(current_node->next->argv[0], O_WRONLY|O_APPEND, 0777);
			else if (current_node->operator == RDR_OUT_REPLACE)
				open(current_node->next->argv[0], O_WRONLY|O_TRUNC|O_CREAT, 0777);
		}
		current_node->operator = NONE;
		exec_cmd(current_node, envp);
	}
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_vector	var_vec;
	char		*input;
	t_statement	*statement_list;

	(void)argc;
	(void)argv;
	var_vec = vec_new();
	config_signals();
	welcome_art();
	while (1)
	{
		input = readline("$ ");
		// CTRL+D
		if (input == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			rl_clear_history();
			free_vec(&var_vec);
			exit(EXIT_SUCCESS);
		}
		if (input[0] == '\0')
			continue;
		add_history(input);
		// exit must be applied without forking
		if (streq(input, "exit"))
		{
			rl_clear_history();
			free_vec(&var_vec);
			exit(EXIT_SUCCESS);
		}
		statement_list = parse_input(input, &var_vec);
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
			else if (ft_strchr(statement_list->argv[0], '='))
				save_user_vars(statement_list->argv[0], &var_vec);
			else if (fork() == 0)
			{
				exec_cmd(statement_list, envp);
				exit(EXIT_SUCCESS);
			}
			wait(NULL);
		}
		else
		{
			if (fork() == 0)
				exec_cmd(statement_list, envp);
			wait(NULL);
		}
		lstclear(&statement_list);
	}
	return (EXIT_SUCCESS);
}

// WEXITSTATUS(returnValue);