/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:57:53 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/14 22:39:17 by nnuno-ca         ###   ########.fr       */
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
	bool	new_line;
	size_t	i;
	size_t	j;
	char	*line;

	new_line = true;
	i = 1;
	// echo with no message || echo -n with no message
	if (!statement->argv[1])
		return ;
	if (streq(statement->argv[i], "-n"))
	{
		if (!statement->argv[2])
			return ;
		new_line = false;
		i++;
	}
	while (statement->argv[i])
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
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
}
