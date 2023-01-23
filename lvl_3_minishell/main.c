/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:02:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/23 00:46:07 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	TODO 

 * handle "", parsing should recognize that the text between
	dquotes is only 1 argument and trim them

 * ls -la |      must wait for input, for the user to provide the right
				 side of the pipe

 * Trying to access an user-defined-env_variable is segfaulting
	E.g echo $USER or echo $4

 * lexer -> parser -> expander -> executor https://github.com/Swoorup/mysh

*/

int	g_exit_status = 0;

char	*get_input(void)
{
	char	*raw_input;
	char	*input;

	raw_input = readline("minishell$ ");
	input = ft_strtrim(raw_input, " \t");
	free(raw_input);
	return (input);
}

int	main(int ac, char **av, char **envp)
{
	t_data		data;
	t_statement	*statement_list;
	char		*input;

	setup_shell(ac, av, envp, &data, &statement_list);
	while (1)
	{
		input = get_input();
		// CTRL + D 
		if (input == NULL)
		{
			free(input);
			cmd_exit(&statement_list, 127, &data);
		}
		if (input[0] == '\0')
			continue ;
		add_history(input);
		statement_list = parse_input(input, &data);
		exec_type(statement_list, &data);
		wait(&g_exit_status);
		if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		lstclear(&statement_list);
	}
	return (EXIT_SUCCESS);
}
