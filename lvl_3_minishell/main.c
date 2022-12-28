/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:02:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/28 20:09:59 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
int			g_exit_status = 0;


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

//TODO 
//		handle "", parsing should recognize that the text between dquotes is only 1 argument and trim them
//		exit with 1 paramater

int	main(int argc, char **argv, char **envp)
{
	t_vector	var_vec;
	t_vector	envp_vec; //exported vars
	int			g_exit_status;
	char		*raw_input;
	char		*input;
	t_statement	*statement_list;

	(void)argc;
	(void)argv;
	g_exit_status = 0;
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
		statement_list = parse_input(input, &var_vec, &envp_vec, g_exit_status);
		free(input);		
		if (lstsize(statement_list) == 1)
		{
			if (!cmd_check_singles(statement_list, &envp_vec, &var_vec) && fork() == 0)
			{
				exec_cmd(statement_list, envp, &envp_vec);
				exit(EXIT_SUCCESS);
			}
		}
		else
			if (fork() == 0)
				exec_cmd(statement_list , envp, &envp_vec);
		wait(&g_exit_status);
		if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		lstclear(&statement_list);
	}
	return (EXIT_SUCCESS);
}
