/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 13:31:56 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/18 20:23:20 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	exit_shell(int exit_status, t_data *data)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	g_exit_status = exit_status;
	if (data)
		destroy(data);
	exit(g_exit_status);
}

static int	unclosed_quotes(char *str)
{
	char	last_opened;

	last_opened = 0;
	while (*str && !last_opened)
	{
		if (*str == '\'' || *str == '"')
			last_opened = *str;
		str++;
	}
	while (*str && last_opened)
	{
		if (*str && *str == last_opened)
			last_opened = 0;
		str++;
	}
	if (*str)
		return (unclosed_quotes(str));
	else if (!last_opened)
		return (0);
	else
		return (1);
}

static bool	invalid_syntax2(char *input)
{
	if (input[0] == '|')
	{
		ft_putendl_fd(SYTX_ERR_PIPE, STDERR_FILENO);
		return (true);
	}
	if (input[0] == '(' || input[0] == '{' || input[0] == '\\')
	{
		ft_putendl_fd(NO_SYTX_PROMPT, STDERR_FILENO);
		return (true);
	}
	if (input[0] == ')')
	{
		ft_putendl_fd(ERR_BRACE_F, STDERR_FILENO);
		return (true);
	}
	return (false);
}

static bool	invalid_syntax(char *input)
{
	if (input[0] == '}')
	{
		ft_putendl_fd(ERR_RECT_BRACE_F, STDERR_FILENO);
		return (true);
	}
	if (input[ft_strlen(input) - 1] == '|')
	{
		ft_putendl_fd(NO_PIPE_PROMPT, STDERR_FILENO);
		return (true);
	}
	if (is_onstr(REDIRECTS, input[ft_strlen(input) - 1]))
	{
		ft_putendl_fd(SYTX_ERR_RDR, STDERR_FILENO);
		return (true);
	}
	return (false);
}

bool	valid_input(char *input, t_data *data)
{
	bool	valid;

	valid = true;
	if (input == NULL)
	{
		free(input);
		exit_shell(EXIT_SUCCESS, data);
	}
	if (input[0] == '\0')
		valid = false;
	else if (unclosed_quotes(input))
	{
		ft_putendl_fd(UNCLOSED_QUOTES, STDERR_FILENO);
		valid = false;
	}
	else if (invalid_syntax(input) || invalid_syntax2(input))
		valid = false;
	if (!valid)
	{
		free(input);
		g_exit_status = 2;
	}
	return (valid);
}
