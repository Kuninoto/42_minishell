/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:13:35 by roramos           #+#    #+#             */
/*   Updated: 2023/02/22 17:08:40 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_exit_status;

size_t	expand_exit_status(char *expanded_input_at_i, size_t *i)
{
	char	*exit_status;
	size_t	j;

	*i += 2;
	exit_status = ft_lltoa(g_exit_status);
	j = 0;
	while (exit_status[j])
	{
		expanded_input_at_i[j] = exit_status[j];
		j += 1;
	}
	free(exit_status);
	return (j);
}

size_t	expand_variable(char *expanded_input_at_i, char *input,
	size_t *i, t_data *data)
{
	char	*var_value;
	size_t	size;
	size_t	j;
	size_t	k;

	size = 0;
	j = 0;
	k = 0;
	*i += 1;
	if (!input[*i] || input[*i] == ' ' || input[*i] == '\"')
	{
		expanded_input_at_i[0] = '$';
		return (1);
	}
	while (input[*i + size] && input[*i + size] != ' '
		&& input[*i + size] != '\"' && !is_onstr(QUOTES, input[*i + size])
		&& input[*i + size] != '$')
		size += 1;
	var_value = get_varvalue_fromvlst(ft_substr(input, *i, size), data);
	*i += size;
	if (!var_value)
		return (0);
	while (var_value[k])
		expanded_input_at_i[j++] = var_value[k++];
	return (j);
}

char	*expander(char *input, t_data *data)
{
	size_t	i;
	size_t	j;
	bool	in_quotes;
	bool	in_dquotes;
	char	*expanded_input;

	init_vars(&i, &j, &in_quotes, &in_dquotes);
	expanded_input = malloc((expanded_size(input, data) + 1) * sizeof(char));
	while (input[i])
	{
		if (input[i] == '\"' && !in_quotes)
			in_dquotes = !in_dquotes;
		if (input[i] == '\'' && !in_dquotes)
			in_quotes = !in_quotes;
		if (input[i] == '$' && input[i + 1] == '?' && !in_quotes)
			j += expand_exit_status(&(expanded_input[j]), &i);
		else if (input[i] && input[i] == '$' && !in_quotes)
			j += expand_variable(&(expanded_input[j]), input, &i, data);
		else
			expanded_input[j++] = input[i++];
	}
	expanded_input[j] = '\0';
	free(input);
	return (expanded_input);
}
