/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 21:53:21 by roramos           #+#    #+#             */
/*   Updated: 2022/12/29 17:49:38 by roramos          ###   ########.fr       */
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
	else
		return (false);
	return (true);
}

bool	cmd_check_singles(t_statement *statement,
	t_vector *envp_vec, t_vector *var_vec)
{
	if (streq(statement->argv[0], "unset"))
	{
		if (is_onvec(statement->argv[1], envp_vec))
			vec_pop_at(statement->argv[1], envp_vec);
	}
	else if (streq(statement->argv[0], "export"))
		cmd_export(envp_vec, var_vec, statement->argv[1]);
	else if (streq(statement->argv[0], "cd"))
		cmd_cd(statement->argv[1]);
	else if (ft_strchr(statement->argv[0], '='))
		save_user_vars(statement->argv[0], var_vec);
	else
		return (false);
	return (true);
}
