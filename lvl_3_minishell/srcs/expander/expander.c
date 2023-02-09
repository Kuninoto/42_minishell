/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:13:35 by roramos           #+#    #+#             */
/*   Updated: 2023/02/09 18:48:38 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

size_t	expand_exit_status(char *expanded_input_at_i, size_t *i)
{
	char	*exit_status;
	size_t	j;

	*i += 2;
	exit_status = ft_itoa(g_exit_status);
	j = 0;
	while (exit_status[j])
	{
		expanded_input_at_i[j] = exit_status[j];
		j += 1;
	}
	free(exit_status);
	return (j);
}

size_t	expand_variable(char *expandend_input_at_i, char *input,
	size_t *i, t_data *data)
{
	char	*var_name;
	char	*var_value;
	size_t	size;
	size_t	j;
	size_t	k;

	size = 0;
	j = 0;
	k = 0;
	printf("j = %zu\n", j);
	*i += 1;
	while (input[*i + size] && input[*i + size] != '$'
		&& input[*i + size] != ' ')
		size += 1;
	var_name = ft_substr(input, *i, size);
	var_value = get_fromvlst(var_name, &data->envp_lst);
	free(var_name);
	if (!var_value)
		return (0);
	while (var_value[k])
		expandend_input_at_i[j++] = var_value[k++];
	*i += size;
	return (j);
}

char	*expander(char *input, t_data *data)
{
	char	*expanded_input;
	size_t	i;
	size_t	j;
	bool	in_quotes;

	i = 0;
	j = 0;
	in_quotes = false;
	expanded_input = malloc((expanded_size(input, data) + 1) * sizeof(char));
	printf("a %d\n",expanded_size(input, data));
	while (input[i])
	{
		if (input[i] == '\'')
			in_quotes = !in_quotes;
		if (input[i] == '$' && input[i + 1] == '?' && !in_quotes)
			j += expand_exit_status(&(expanded_input[j]), &i);
		else if (input[i] && input[i] == '$' && !in_quotes)
			j += expand_variable(&(expanded_input[j]), input, &i, data);
		else
			expanded_input[j++] = input[i++];
	}
	printf("j %zu %zu\n", j, i);
	expanded_input[j] = '\0';
	free(input);
	return (expanded_input);
}
