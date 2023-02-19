/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 13:31:56 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/19 19:08:00 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	exit_shell(int exit_status, t_data *data)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	g_exit_status = exit_status;
	if (data)
		destroy(data);
	exit(g_exit_status);
}

bool	valid_input(char *input, t_data *data)
{
	bool	valid;

	valid = true;
	if (input == NULL)
	{
		free(input);
		exit_shell(EXIT_SUCCESS, data);
	}
	if (input[0] == '\0')
		valid = false;
	else if (unclosed_quotes(input))
	{
		ft_putendl_fd(UNCLOSED_QUOTES, STDERR_FILENO);
		valid = false;
	}
	else if (invalid_syntax(input) || invalid_syntax2(input))
		valid = false;
	if (!valid)
	{
		free(input);
		g_exit_status = 2;
	}
	return (valid);
}
