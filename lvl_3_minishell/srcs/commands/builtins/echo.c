/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:57:53 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/11 03:18:48 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print(t_statement *statement, int i)
{
	char	*line;
	size_t	j;

	line = statement->argv[i];
	j = 0;
	while (line[j])
	{
		if (line[j] == '\\')
		{
			j += 1;
			continue ;
		}
		ft_putchar_fd(line[j], STDOUT_FILENO);
		j += 1;
	}
}

int	cmd_echo(t_statement *statement)
{
	bool	has_n;
	int		i;

	has_n = streq(statement->argv[1], "-n");
	i = 1;
	if (has_n)
	{
		if (!statement->argv[2])
			return (EXIT_SUCCESS);
		i = 2;
	}
	while (i != statement->argc)
	{
		print(statement, i);
		if (statement->argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i += 1;
	}
	if (!has_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
