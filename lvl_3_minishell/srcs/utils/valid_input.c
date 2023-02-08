/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 13:31:56 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/08 14:53:57 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_putendl_fd(STARTS_WITH_PIPE, STDERR_FILENO);
		return (true);
	}
	else if (input[0] == '>' || input[0] == '<')
	{
		ft_putendl_fd(STARTS_WITH_REDIR, STDERR_FILENO);
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
	else if (unclosed_quotes(input))
	{
		ft_putendl_fd(UNCLOSED_QUOTES, STDERR_FILENO);
		valid = false;
	}
	else if (invalid_syntax(input))
		valid = false;
	if (!valid)
		free(input);
	return (valid);
}
