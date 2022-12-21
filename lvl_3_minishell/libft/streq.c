/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   streq.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:18:00 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/20 19:32:02 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	streq(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	if (str1 && !str2)
		return (false);
	if (!str1 && str2)
		return (false);
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (false);
		i++;
	}
	return (true);
}
