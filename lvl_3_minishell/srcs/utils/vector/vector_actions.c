/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:33:46 by roramos           #+#    #+#             */
/*   Updated: 2023/01/23 18:21:01 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	vec_push(t_vector *vector, char	*str)
{
	if (vector->count == vector->capacity)
		vec_realloc(vector);
	vector->storage[vector->count] = str;
	vector->count += 1;
}

char	*vec_pop(t_vector *vector)
{
	char	*str;

	str = vector->storage[vector->count - 1];
	free(vector->storage[vector->count - 1]);
	vector->storage[vector->count - 1] = NULL;
	vector->count -= 1;
	return (str);
}
