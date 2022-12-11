/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:57:53 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/11 18:27:19 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_echo(char **inputs)
{
	size_t 	i;
	bool	next_line;

	next_line = true;
	i = 1;		
	if (ft_strncmp(inputs[i], "-n\0", 3) == 0)
	{
		next_line = false;
		i++;
	}	
	while (inputs[i])
	{
		ft_putstr_fd(ft_strtrim(inputs[i], "\""), STDOUT_FILENO);
		if (inputs[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if(next_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	
}
