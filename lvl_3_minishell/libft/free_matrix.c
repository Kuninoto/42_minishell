/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:57:16 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/10 20:01:53 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);

}