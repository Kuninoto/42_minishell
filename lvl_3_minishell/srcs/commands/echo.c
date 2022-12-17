/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:57:53 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/17 19:19:43 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	has_quotes(char *line)
{
	if (ft_strchr(line, '\"') || ft_strchr(line, '\''))
		return (true);
	else
		return (false);
}

void	cmd_echo(t_statement *statement)
{
	bool	has_n;
	int		i;
	int		j;
	char	*line;

	// echo with no message
	if (!statement->argv[1])
		return ;
	has_n = streq(statement->argv[1], "-n");
	i = 1;
	if (has_n)
	{
		// echo -n with no message
		if (!statement->argv[2])
			return ;
		i = 2;
	}
	while (i != statement->argc)
	{
		if (has_quotes(statement->argv[i]))
		{
			line = ft_strtrim(statement->argv[i], "\"'");
			ft_putstr_fd(line, STDOUT_FILENO);
		}
		else
		{
			line = statement->argv[i];
			j = -1;
			while (line[++j])
			{
				if (line[j] == '\\')
					continue ;
				ft_putchar_fd(line[j], STDOUT_FILENO);
			}
		}
		if (statement->argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
		free(line);
	}
	if (!has_n)
		write(STDOUT_FILENO, "\n", 1);
}
