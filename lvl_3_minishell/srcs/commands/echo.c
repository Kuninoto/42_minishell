/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:57:53 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/10 20:18:44 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_echo(char **inputs)
{
	size_t i;

	i = 1;
	if (ft_strnstr(inputs[i], "-n", 3))
	{
		while (inputs[i])
		{
			write(STDOUT_FILENO, inputs[i], ft_strlen(inputs[i]));
			i++;
		}
		return ;
	}
	while (inputs[i])
	{
		write(STDOUT_FILENO, inputs[i], ft_strlen(inputs[i]));
		i++;
	}
	write(STDOUT_FILENO, "\n", 1);
}
