/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 13:31:56 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/30 22:37:25 by nnuno-ca         ###   ########.fr       */
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
	if (starts_with_pipe(input))
	{
		ft_putendl_fd(STARTS_WITH_PIPE, STDERR_FILENO);
		return (true);
	}
	return (false);
}

bool	valid_input(char *input, t_statement *statement_list, t_data *data)
{
	bool	valid;
	
	valid = true;
	if (input == NULL)
	{
		free(input);
		cmd_exit(statement_list, 127, data);
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
