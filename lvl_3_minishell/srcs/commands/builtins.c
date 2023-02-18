/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:24:53 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/18 17:29:02 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	call_cmd_exit(t_statement *s, t_data *data)
{
	if (s->argc == 2)
	{
		if (is_all_digits(s->argv[1]))
			cmd_exit(ft_atoi(s->argv[1]), data);
		else
			cmd_exit(2, data);
	}
	else if (s->argc > 2)
		cmd_exit(EXIT_FAILURE, data);
	else
		cmd_exit(EXIT_SUCCESS, data);
}

bool	builtin(t_statement *s, t_data *data)
{
	if (streq(s->argv[0], "exit"))
		call_cmd_exit(s, data);
	else if (streq(s->argv[0], "unset"))
		g_exit_status = cmd_unset(s->argv[1], &data->envp_lst);
	else if (streq(s->argv[0], "export"))
		g_exit_status = cmd_export(s, data);
	else if (streq(s->argv[0], "cd"))
	{
		if (s->argc > 2)
			g_exit_status = cd_too_many_args();
		else
			g_exit_status = cmd_cd(s->argv[1]);
	}
	else if (ft_strchr(s->argv[0], '=') && !is_digit(s->argv[0][0]))
		g_exit_status = save_user_vars(s->argv[0],
				&data->envp_lst, false);
	else if (streq(s->argv[0], "echo"))
		g_exit_status = cmd_echo(s);
	else if (streq(s->argv[0], "pwd"))
		g_exit_status = cmd_pwd();
	else if (streq(s->argv[0], "env"))
		g_exit_status = cmd_env(data);
	else
		return (false);
	return (true);
}
