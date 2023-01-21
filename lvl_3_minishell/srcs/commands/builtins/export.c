/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:03:10 by roramos           #+#    #+#             */
/*   Updated: 2023/01/20 22:10:32 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_export(t_data *data, char *var_name)
{
	char	*var_value;
	char	**splitted;

	splitted = ft_split(var_name, '=');
	var_value = is_onvec(splitted[0], &data->envp_vec);
	if (var_value)
		vec_pop_at(splitted[0], &data->envp_vec);
	if (!ft_strchr(var_name, '='))
	{
		var_value = is_onvec(splitted[0], &data->var_vec);
		if (!var_value)
			return ;
		var_value = join_freev2("=", var_value);
		var_name = join_freev2(var_name, var_value);
		vec_push(&data->envp_vec, ft_strcpy(var_name));
		free(var_name);
		return ;
	}
	vec_push(&data->envp_vec, ft_strcpy(var_name));
	free (var_value);
}
