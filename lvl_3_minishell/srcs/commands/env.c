/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 23:29:50 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/29 17:48:50 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_env(char **envp, t_vector *envp_vec)
{
	int	i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
	i = -1;
	while (envp_vec->storage[++i])
		printf("%s\n", envp_vec->storage[i]);
}
