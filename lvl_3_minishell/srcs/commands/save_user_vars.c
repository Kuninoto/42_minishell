/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_user_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:33:28 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/20 18:16:48 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	save_user_vars(char *user_var, t_vector *var_vec)
{
	char	*trimmed;

	trimmed = ft_strtrim(user_var, " ");
	vec_push(var_vec, trimmed);
}