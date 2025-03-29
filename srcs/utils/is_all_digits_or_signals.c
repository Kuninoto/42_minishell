/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_all_digits_or_signals.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:06:31 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/18 19:56:08 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_all_digits_or_signals(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!is_digit(str[i]) && str[i] != '-' && str[i] != '+')
			return (false);
		i += 1;
	}
	return (true);
}
