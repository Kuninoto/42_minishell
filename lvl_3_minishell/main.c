/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:02:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/25 19:15:15 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		statement_list = parser(input, &data);
		if (statement_list == NULL)
		{
			free(input);
			ft_putstr_fd("minishell: unclosed quotes. My devs didn't want to develop quote nor dquote prompt\n", STDERR_FILENO);
			continue ;
		}
		exec_type(statement_list, &data);
		wait(&g_exit_status);
		if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		lstclear(&statement_list);
	}
	return (EXIT_SUCCESS);
}
