/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:17:34 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/19 23:24:39 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_exit_status;

static void	exit_non_numeric_arg(void)
{
	g_exit_status = 2;
	ft_putendl_fd(EXIT_NON_NUMERIC_ARG, STDERR_FILENO);
}

void	cmd_exit(t_statement *s, t_data *data)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (s->argc == 2)
	{
		if (is_all_digits_or_signals(s->argv[1]))
		{
			if (!fits_in_longlong(s->argv[1]))
				exit_non_numeric_arg();
			else
				g_exit_status = ft_atoll(s->argv[1]);
		}
		else
			exit_non_numeric_arg();
	}
	else if (s->argc > 2)
	{
		g_exit_status = EXIT_FAILURE;
		ft_putendl_fd(EXIT_TOO_MANY_ARGS, STDERR_FILENO);
	}
	else
		g_exit_status = EXIT_SUCCESS;
	if (data)
		destroy(data);
	exit(g_exit_status);
}
