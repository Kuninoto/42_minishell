/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:45:44 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/19 18:05:53 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unclosed_quotes(char *str)
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

bool	unexpected_token(char token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
	ft_putchar_fd(token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	return (true);
}

bool	has_operators(char *input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (is_onstr(OPERATORS, input[i]))
			return (true);
		i += 1;
	}
	return (false);
}

// OPERATORS
bool	invalid_syntax3(char *input)
{
	size_t	i;

	i = 0;
	if (!has_operators(input))
		return (false);
	while (input[i] && !is_onstr(OPERATORS, input[i]))
		i += 1;
	if ((input[i] == '>' && input[i + 1] == '<')
	|| (input[i] == '<' && input[i + 1] == '>')
	|| (input[i] == '|' && input[i + 1] == '|')
	|| (input[i] == '&' && input[i + 1] == '&'))
		return (unexpected_token(input[i + 1]));
	return (false);	
}

bool	invalid_syntax2(char *input)
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

bool	invalid_syntax(char *input)
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
