/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:12:43 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/20 18:29:43 by nnuno-ca         ###   ########.fr       */
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
	vector->count--;
	return (instruction);
}

void	vec_realloc(t_vector *vector)
{
	size_t	i;
	char	**buf;

	vector->capacity *= 2;
	i = 0;
	buf = malloc(vector->capacity * sizeof(char *));
	while (i < vector->count)
	{
		buf[i] = vector->storage[i];
		i++;
	}
	free(vector->storage);
	vector->storage = buf;
}

void	free_vec(t_vector *vector)
{
	size_t	i;

	i = 0;
	while (i < vector->count)
	{
		free(vector->storage[i]);
		i++;
	}
	free(vector->storage);
}

char	*is_onvec(char *user_var, t_vector *vector)
{
	size_t	i;
	char	**splitted;

	i = 0;
	while (i < vector->count)
	{
		splitted = ft_split(vector->storage[i], '=');
		if (streq(splitted[0], user_var))
			return (splitted[1]);
		free(splitted);
		i++;
	}
	return (NULL);
}
