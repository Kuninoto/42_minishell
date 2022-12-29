/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:33:46 by roramos           #+#    #+#             */
/*   Updated: 2022/12/29 17:34:30 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	vec_push(t_vector *vector, char	*instruction)
{
	if (vector->count == vector->capacity)
		vec_realloc(vector);
	vector->storage[vector->count] = instruction;
	vector->count++;
}

char	*vec_pop(t_vector *vector)
{
	char	*instruction;

	instruction = vector->storage[vector->count - 1];
	free(vector->storage[vector->count - 1]);
	vector->storage[vector->count - 1] = NULL;
	vector->count--;
	return (instruction);
}
