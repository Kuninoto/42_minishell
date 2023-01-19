/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 21:53:21 by roramos           #+#    #+#             */
/*   Updated: 2023/01/19 23:17:04 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	builtin(t_statement *statement, t_data *data)
{
	if (streq(statement->argv[0], "echo"))
		cmd_echo(statement);
	else if (streq(statement->argv[0], "pwd"))
		cmd_pwd();
	else if (streq(statement->argv[0], "env"))
		cmd_env(data);
	/* Must check for valid */
	else if (streq(statement->argv[0], "exit"))
		cmd_exit(&statement, ft_atoi(statement->argv[1]), data);
	else
		return (false);
	return (true);
}

bool	cmd_check_singles(t_statement *statement, t_data *data)
{
	if (streq(statement->argv[0], "unset"))
	{
		if (is_onvec(statement->argv[1], &data->envp_vec))
			vec_pop_at(statement->argv[1], &data->envp_vec);
	}
	else if (streq(statement->argv[0], "export"))
		cmd_export(data, statement->argv[1]);
	else if (streq(statement->argv[0], "cd"))
		cmd_cd(statement->argv[1]);
	else if (ft_strchr(statement->argv[0], '='))
		save_user_vars(statement->argv[0], &data->var_vec);
	else
		return (false);
	return (true);
}
