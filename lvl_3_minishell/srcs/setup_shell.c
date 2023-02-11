/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:17:06 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/11 06:22:11 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_shell(char **envp, t_data *data, t_statement **statement_list)
{
	data->envp = envp;
	data->envp_lst = init_envp_lst(envp);
	data->head = NULL;
	*statement_list = NULL;
	config_signals();
}
