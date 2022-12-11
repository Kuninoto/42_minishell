/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:57:53 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/11 23:17:56 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_echo(char **inputs)
{
	bool	new_line;
	size_t	i;
	char	*line;

	new_line = true;
	i = 1;
	if (ft_strncmp(inputs[i], "-n\0", 3) == 0)
	{
		new_line = false;
		i++;
	}	
	while (inputs[i])
	{
		line = ft_strtrim(inputs[i], "\"");
		ft_putstr_fd(line, STDOUT_FILENO);
		if (inputs[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
		free(line);
	}
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);	
}
