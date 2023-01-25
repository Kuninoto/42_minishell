/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:12:43 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/25 19:38:23 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	vec_realloc(t_vector *vector)
{
	char	**buf;
	size_t	i;

	if (vector->capacity == 1)
		vector->capacity = 8;
	else
		vector->capacity *= 2;
	buf = malloc(vector->capacity * sizeof(char *));
	i = 0;
	while (i < vector->count)
	{
		buf[i] = vector->storage[i];
		i += 1;
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
		i += 1;
	}
	free(vector->storage);
}

void	vec_pop_at(char *user_var, t_vector *vector)
{
	size_t	i;

	if (vector->count != 1)
	{
		i = 0;
		while (i < vector->count && !ft_strncmp(vector->storage[i], user_var,
				ft_strlen(vector->storage[i])))
		{
			ft_putstr_fd(vector->storage[i], STDOUT_FILENO);
			i += 1;
		}
		while (i < vector->count + 1)
		{
			vector->storage[i] = vector->storage[i + 1];
			i += 1;
		}
	}
	vec_pop(vector);
}

char	*is_onvec(char *to_search, t_vector *vector)
{
	size_t	i;
	char	**splitted;

	i = 0;
	while (i < vector->count)
	{
		splitted = ft_split(vector->storage[i], '=');
		if (streq(splitted[0], to_search))
		{
			free_matrix(splitted);
			return (vector->storage[i]);
		}
		free_matrix(splitted);
		i += 1;
	}
	return (NULL);
}

char	*get_fromvec(char *user_var, t_vector *vector)
{
	size_t	i;
	char	**splitted;
	char	*var;

	i = 0;
	while (i < vector->count)
	{
		splitted = ft_split(vector->storage[i], '=');
		if (streq(splitted[0], user_var))
		{
			var = ft_strcpy(splitted[1]);
			free_matrix(splitted);
			return (var);
		}
		free_matrix(splitted);
		i += 1;
	}
	return (NULL);
}
