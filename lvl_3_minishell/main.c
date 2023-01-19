/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:02:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/19 23:10:04 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*	TODO 
* handle "", parsing should recognize that the text between
	dquotes is only 1 argument and trim them
* exit with 1 paramater
*/

int	g_exit_status = 0;

char	*get_input(void)
{
	char	*raw_input;
	char	*input;

	raw_input = readline("$ ");
	input = ft_strtrim(raw_input, " \t");
	free(raw_input);
	return (input);
}

char	**get_paths(char **envp)
{
	size_t	i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4) != 0)
		i += 1;
	return (ft_split(envp[i], ':'));
}

void	setup_shell(int ac, char **av, char **envp, t_data *data)
{
	(void)ac;
	(void)av;
	data->envp = envp;
	data->paths = get_paths(envp);
	data->var_vec = vec_new();
	data->envp_vec = vec_new();
	config_signals();
	welcome_art();
}

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	char		*input;
	t_statement	*statement_list;

	setup_shell(argc, argv, envp, &data);
	while (1)
	{
		input = get_input();
		if (input == NULL)
			free(input);
		if (input[0] == '\0')
			continue ;
		add_history(input);
		statement_list = parse_input(input, &data, g_exit_status);
		exec_type(statement_list, &data);
		wait(&g_exit_status);
		if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		lstclear(&statement_list);
	}
	return (EXIT_SUCCESS);
}

/* 
Currently trying to handle exit command with paramaters.
The only issue is that exit should free all malloced stuff (vectors and list)
Thinking on creating a structure to carry around those variables
*/
