/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:02:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/11 05:52:12 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

static char	*get_input(void)
{
	char	*raw_input;
	char	*input;

	raw_input = readline("minishell$ ");
	input = trim_free(raw_input, " \t");
	return (input);
}

int	main(int ac, char **av, char **envp)
{
	t_data		data;
	t_statement	*statement_list;
	char		*input;

	if (av && ac > 1)
		panic(NULL, CL_ARGUMENTS_ERR, EXIT_FAILURE);
	setup_shell(envp, &data, &statement_list);
	while (1)
	{
		input = get_input();
		if (!valid_input(input, &data))
			continue ;
		add_history(input);
		input = expander(input, &data);
		if (!input || !input[0])
		{
			free(input);
			continue ;
		}
		statement_list = parser(input);
		exec_type(statement_list, &data);
		p_lstclear(statement_list);
	}
	return (EXIT_SUCCESS);
}
