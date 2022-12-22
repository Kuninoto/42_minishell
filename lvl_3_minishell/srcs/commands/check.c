/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 21:53:21 by roramos           #+#    #+#             */
/*   Updated: 2022/12/22 15:16:07 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	cmd_check(t_statement *statement, char **envp, t_vector *envp_vec)
{
	if (streq(statement->argv[0], "echo"))
		cmd_echo(statement);
	else if (streq(statement->argv[0], "pwd"))
		cmd_pwd();
	else if (streq(statement->argv[0], "env"))
		cmd_env(envp, envp_vec);
/* 	else if (statement->argv[0][0] ==  '$')
		print_env_variables(&statement->argv[0][1]); */
	//else if (ft_strchr(statement->argv[0], '='))
	else
		return (false);
	return (true);
}