/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:17:06 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/27 14:00:28 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_shell(int ac, char **av, char **envp, t_data *data, t_statement **statement_list)
{
	(void)ac;
	(void)av;
	data->envp = envp;
	data->envp_lst = init_envp_lst(envp);
	*statement_list = NULL;
	config_signals();
}