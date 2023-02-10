/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:23:00 by roramos           #+#    #+#             */
/*   Updated: 2023/02/10 00:51:12 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_operator	get_operator(char *operator)
{
	if (!operator)
		return (NONE);
	if (streq(operator, "|"))
		return (PIPE);
	if (streq(operator, ">>"))
		return (RDR_OUT_APPEND);
	if (streq(operator, ">"))
		return (RDR_OUT_REPLACE);
	if (streq(operator, "<<"))
		return (RDR_INPUT_UNTIL);
	if (streq(operator, "<"))
		return (RDR_INPUT);
	return (NONE);
}

size_t	get_argc(char **parsed)
{
	size_t	i;

	i = 0;
	while (parsed[i])
		i += 1;
	return (i);
}

size_t	get_token_len(char *input_at_i)
{
	size_t	i;
	char	quotes;

	i = 0;
	if (is_onstr(REDIRECTS, input_at_i[i]))
	{
		if (input_at_i[i] == input_at_i[i + 1])
			return (2);
		return (1);
	}
	while (input_at_i[i] && !is_spaces(input_at_i[i]))
	{
		if (is_onstr(QUOTES, input_at_i[i]))
		{
			quotes = input_at_i[i++];
			while (input_at_i[i] && input_at_i[i] != quotes)
				i += 1;
		}
		i += 1;
	}
	return (i);
}

size_t	get_nr_statements(char *input)
{
	size_t	count;
	bool	flag;
	bool	has_quotes;

	count = 0;
	flag = false;
	has_quotes = false;
	while (*input)
	{
		if (is_onstr(REDIRECTS, *input))
			count += 1;
		if (is_onstr(QUOTES, *input) && *input == *(input + 1))
			input += 2;
		else if (is_onstr(QUOTES, *input))
			has_quotes = !has_quotes;
		if (*input != ' ' && !flag && !has_quotes)
		{
			flag = true;
			count += 1;
		}
		else if (*input == ' ')
			flag = false;
		input += 1;
	}
	return (count);
}
