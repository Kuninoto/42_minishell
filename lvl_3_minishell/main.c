/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:02:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/07 21:04:12 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*	TODO 
* handle "", parsing should recognize that the text between
	dquotes is only 1 argument and trim them
* exit with 1 paramater
* search for the binary in all the PATH env variable, not only on /usr/bin
	char	**get_paths(char **envp)
	{
		size_t	i;

		i = 0;
		while (ft_strncmp("PATH", envp[i], 4) != 0)
			i += 1;
		return (ft_split(envp[i], ':'));
	}

	char	*get_bin_path(char *cmd, char **paths)
	{
		size_t	i;
		char	*tmp;
		char	*bin_path;

		i = 0;
		while (paths[i])
		{
			tmp = ft_strjoin(paths[i], "/");
			bin_path = join_free(tmp, cmd);
			if (access(bin_path, F_OK) == 0)
				return (bin_path);
			free(bin_path);
			i += 1;
		}
		return (bin_path);
	}

*/
char	*get_input(void)
{
	char	*raw_input;
	char	*input;

	raw_input = readline("$ ");
	input = ft_strtrim(raw_input, " \t");
	free(raw_input);
	return (input);
}

void	setup_shell(int ac, char **av, t_vector *var_vec, t_vector *envp_vec)
{
	(void)ac;
	(void)av;
	*var_vec = vec_new();
	*envp_vec = vec_new();
	config_signals();
	welcome_art();
}

int	main(int argc, char **argv, char **envp)
{
	int			exit_status;
	t_vector	var_vec;
	t_vector	envp_vec;
	char		*input;
	t_statement	*statement_list;

	exit_status = 0;
	setup_shell(argc, argv, &var_vec, &envp_vec);
	while (1)
	{
		input = get_input();
		if (input == NULL || streq(input, "exit"))
		{
			free(input);
			cmd_exit(true, &var_vec, &envp_vec);
		}
		if (input[0] == '\0')
			continue ;
		add_history(input);
		statement_list = parse_input(input, &var_vec, &envp_vec, exit_status);
		exec_type(statement_list, envp, &envp_vec, &var_vec);
		wait(&exit_status);
		if (WIFEXITED(exit_status))
			exit_status = WEXITSTATUS(exit_status);
		lstclear(&statement_list);
	}
	return (EXIT_SUCCESS);
}

/* 
Currently trying to handle exit command with paramaters.
The only issue is that exit should free all malloced stuff (vectors and list)
Thinking on creating a structure to carry around those variables
*/
