/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:24:53 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/19 22:53:22 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_exit_status;

bool	is_valid_id(char *str)
{
	size_t	i;

	i = 0;
	if (streq(str, "="))
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (is_digit(str[i]) || str[i] == '!' || str[i] == '@'
			|| str[i] == '{' || str[i] == '}' || str[i] == '-')
			return (false);
		i += 1;
	}
	return (true);
}

static int	call_cmd_unset(t_statement *s, t_data *data)
{
	if (s->argc == 1)
		return (EXIT_SUCCESS);
	return (cmd_unset(s->argv[1], &data->envp_lst));
}

static int	call_cmd_cd(t_statement *s, t_data *data)
{
	if (s->argc > 2)
		return (cd_too_many_args());
	else
		return (cmd_cd(s->argv[1], data));
}

bool	builtin(t_statement *s, t_data *data)
{
	if (streq(s->argv[0], "exit"))
		cmd_exit(s, data);
	else if (streq(s->argv[0], "unset"))
		g_exit_status = call_cmd_unset(s, data);
	else if (streq(s->argv[0], "export"))
		g_exit_status = cmd_export(s, data);
	else if (streq(s->argv[0], "cd"))
		g_exit_status = call_cmd_cd(s, data);
	else if (ft_strchr(s->argv[0], '=') && is_valid_id(s->argv[0]))
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
