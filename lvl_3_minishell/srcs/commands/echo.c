/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:57:53 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/12 21:10:32 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_echo(char **parsed)
{
	bool	new_line;
	size_t	i;
	char	*line;

	new_line = true;
	i = 1;
	if (ft_strncmp(parsed[i], "-n\0", 3) == 0)
	{
		new_line = false;
		i++;
	}	
	while (parsed[i])
	{
		line = ft_strtrim(parsed[i], "\"");
		ft_putstr_fd(line, STDOUT_FILENO);
		if (parsed[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
		free(line);
	}
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
}
