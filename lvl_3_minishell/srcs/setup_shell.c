/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:17:06 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/20 18:36:52 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	data->envp = envp;
	data->paths = get_paths(envp);
	data->var_vec = vec_new();
	data->envp_vec = vec_new();
	*statement_list = NULL;
	config_signals();
	welcome_art();
}