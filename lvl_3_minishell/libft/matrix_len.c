/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:21:59 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/09 23:56:57 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	matrix_len(char **matrix)
{
	size_t	i;

	i = 0;
	if (!matrix)
		return (0);
	while (matrix[i])
		i += 1;
	return (i);
}
