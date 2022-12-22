/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:03:10 by roramos           #+#    #+#             */
/*   Updated: 2022/12/22 18:06:01 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_export(t_vector *envp_vec, t_vector *var_vec, char *var_name)
{
	char	*var_value;
	char	**splitted;
	
	splitted = ft_split(var_name, '=');
	var_value = is_onvec(splitted[0], envp_vec);
	if (var_value)
		vec_pop_at(splitted[0], envp_vec);
	if (!ft_strchr(var_name, '='))
	{
		var_value = is_onvec(splitted[0], var_vec);
		if (!var_value)
			return ;
		var_value = join_freev2("=", var_value);
		var_name = join_freev2(var_name, var_value);
		vec_push(envp_vec, ft_strcpy(var_name));
		free (var_name);
		return ;
	}
	vec_push(envp_vec, ft_strcpy(var_name));
	free (var_value);
}