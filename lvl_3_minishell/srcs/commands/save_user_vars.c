/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_user_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:33:28 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/29 17:47:45 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	save_user_vars(char *user_var, t_vector *var_vec)
{
	char	*trimmed;

	trimmed = ft_strtrim(user_var, " ");
	vec_push(var_vec, trimmed);
}
