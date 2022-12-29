/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:54:35 by roramos           #+#    #+#             */
/*   Updated: 2022/12/29 17:02:53 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *to_copy)
{
	char		*copy;
	size_t		i;

	copy = malloc((ft_strlen(to_copy) + 1) * sizeof(char));
	i = 0;
	while (to_copy[i])
	{
		copy[i] = to_copy[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
