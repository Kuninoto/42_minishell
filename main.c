/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:02:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/22 16:59:39 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	g_exit_status = 0;

static char	*get_input(void)
{
	char	*raw_input;
	char	*input;

	raw_input = readline("minishell$ ");
	input = trim_free(raw_input, " \t");
	return (input);
}

static void	clean_parsed(t_statement **statement_list, t_data *data)
{
	p_lstclear(statement_list);
	*statement_list = NULL;
	data->head = NULL;
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
		if (!input[0])
		{
			free(input);
			continue ;
		}
		statement_list = parser(input);
		data.head = statement_list;
		exec_type(statement_list, &data);
		clean_parsed(&statement_list, &data);
	}
	return (EXIT_SUCCESS);
}
