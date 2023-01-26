/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:17:06 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/26 18:08:13 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(char **envp)
{
	size_t	i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4) != 0)
		i += 1;
	return (ft_split(envp[i], ':'));
}


void	setup_shell(int ac, char **av, char **envp, t_data *data, t_statement **statement_list)
{
	(void)ac;
	(void)av;
	data->paths = get_paths(envp);
	data->envp = envp;
	data->envp_lst = init_envp_lst(envp);
	*statement_list = NULL;
	config_signals();
}