/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 13:31:56 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/11 12:49:01 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

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

static bool	invalid_syntax(char *input)
{
	if (input[0] == '|')
	{
		ft_putendl_fd(SYTX_ERR_PIPE, STDERR_FILENO);
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
		cmd_exit(127, data);
	}
	if (input[0] == '\0')
		valid = false;
	else if (unclosed_quotes(input))
	{
		ft_putendl_fd(UNCLOSED_QUOTES, STDERR_FILENO);
		valid = false;
	}
	else if (invalid_syntax(input))
		valid = false;
	if (!valid)
	{
		free(input);
		g_exit_status = 2;
	}
	return (valid);
}
