/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:57:53 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/26 16:58:46 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_quotesv2(char *line)
{
	if (ft_strchr(line, '\"') || ft_strchr(line, '\''))
		return (true);
	else
		return (false);
}

void	print(t_statement *statement, int i)
{
	int		j;
	char	*line;

	line = statement->argv[i];
	j = -1;
	while (line[++j])
	{
		if (line[j] == '\\')
			continue ;
		ft_putchar_fd(line[j], STDOUT_FILENO);
	}
}

void	cmd_echo(t_statement *statement)
{
	bool	has_n;
	int		i;

	has_n = streq(statement->argv[1], "-n");
	i = 0;
	if (has_n)
	{
		if (!statement->argv[2])
			return ;
		i = 1;
	}
	while (++i != statement->argc)
	{
		print(statement, i);
		if (statement->argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!has_n)
		write(STDOUT_FILENO, "\n", 2);
}
