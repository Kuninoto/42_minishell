/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:02:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/23 15:05:55 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	dismiss_signal(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 1);
		write(STDIN_FILENO, "\n$ ", 3);
	}
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

char	**copy_envs(char **envp)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	j = -1;
	while (envp[i])
		i++;
	temp = malloc(i * sizeof(char *));
	while(++j < i)
		temp[j] = envp[j];
	return (temp);
}

char	**set_envs(char ***envp, char *var)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	j = -1;
	while (envp[0][i])
		i++;
	temp = malloc((i + 2) * sizeof(char *));
	while(++j < i)
		temp[j] = envp[0][j];
	temp[j] = var;
	temp[++j] = NULL;
	free(*envp);
	return (temp);
}

//TODO handle "", parsing should recognize that the text between dquotes is only 1 argument and trim them

int	main(int argc, char **argv, char **envp)
{
	t_vector	var_vec;
	t_vector	envp_vec; //exported vars
	char		*input;
	char		*raw_input;
	t_statement	*statement_list;

	(void)argc;
	(void)argv;
	var_vec = vec_new();
	envp_vec = vec_new();
	config_signals();
	welcome_art();
	while (1)
	{
		raw_input = readline("$ ");
		input = ft_strtrim(raw_input, " \t");
		free(raw_input);
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
		if (streq(input, "exit"))
		{
			rl_clear_history();
			free_vec(&var_vec);
			exit(EXIT_SUCCESS);
		}
		statement_list = parse_input(input, &var_vec, &envp_vec);
		free(input);

/* 		for (t_statement *temp = statement_list; temp != NULL; temp = temp->next)
		{
			printf("ARGC: %d\n", temp->argc);
			printf("ARGV: ");
			for (size_t i = 0; temp->argv[i] != NULL; i++)
				printf("%s ", temp->argv[i]);
			printf("\nOPERATOR: %d\n", temp->operator);
			printf("\n");
		}
		printf("\n"); */
		
		if (lstsize(statement_list) == 1)
		{
			if (streq(statement_list->argv[0], "unset"))
			{
				if (is_onvec(statement_list->argv[1], &envp_vec))
					vec_pop_at(statement_list->argv[1], &envp_vec);
			}
			else if (streq(statement_list->argv[0], "export"))
				cmd_export(&envp_vec, &var_vec, statement_list->argv[1]);
			else if (streq(statement_list->argv[0], "cd"))
				cmd_cd(statement_list->argv[1]);
			else if (ft_strchr(statement_list->argv[0], '='))
				save_user_vars(statement_list->argv[0], &var_vec);
			else if (fork() == 0)
			{
				exec_cmd(statement_list, envp, &envp_vec);
				exit(EXIT_SUCCESS);
			}
			wait(&g_exit_status);
			if (WIFEXITED(g_exit_status))
				g_exit_status = WEXITSTATUS(g_exit_status);
		}
		else
		{
			if (fork() == 0)
				exec_cmd(statement_list, envp, &envp_vec);
			wait(&g_exit_status);
			if (WIFEXITED(g_exit_status))
				g_exit_status = WEXITSTATUS(g_exit_status);
		}
		lstclear(&statement_list);
	}
	return (EXIT_SUCCESS);
}
