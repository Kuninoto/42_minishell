/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:57:53 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/16 12:53:01 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			i += 1;
			continue ;
		}
		ft_putchar_fd(str[i], STDOUT_FILENO);
		i += 1;
	}
}

int	cmd_echo(t_statement *statement)
{
	bool	has_n;
	int		i;

	if (!statement->argv[1])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	i = 1;
	has_n = false;
	if (statement->argc >= 2)
		has_n = streq(statement->argv[1], "-n");
	if (has_n)
		i += 1;
	while (i != statement->argc)
	{
		print(statement->argv[i]);
		if (i + 1 < statement->argc)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i += 1;
	}
	if (!has_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
