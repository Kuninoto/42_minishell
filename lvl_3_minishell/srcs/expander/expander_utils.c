/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:25:28 by roramos           #+#    #+#             */
/*   Updated: 2023/02/20 15:00:24 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_exit_status;

size_t	exit_status_size(void)
{
	char	*exit_status;
	size_t	size;

	exit_status = ft_lltoa(g_exit_status);
	size = ft_strlen(exit_status);
	free(exit_status);
	return (size);
}

size_t	expand_size(char *input_at_i, size_t *i, t_data *data)
{
	size_t	var_size;
	char	*var_name;
	char	*var_value;

	*i += 1;
	if (single_dollar(input_at_i))
		return (1);
	var_size = 0;
	while (input_at_i[var_size + 1]
		&& input_at_i[var_size + 1] != ' '
		&& !is_onstr(QUOTES, input_at_i[var_size + 1])
		&& input_at_i[var_size + 1] != '$')
				var_size += 1;
	if (var_size == 0)
		return (0);
	var_name = ft_substr(input_at_i, 1, var_size);
	var_value = get_fromvlst(var_name, &data->envp_lst);
	free(var_name);
	*i += var_size;
	if (!var_value)
		return (0);
	return (ft_strlen(var_value));
}

int	expanded_size(char *input, t_data *data)
{
	size_t	i;
	size_t	size;
	bool	in_quotes;
	bool	in_d_quotes;

	i = 0;
	size = 0;
	in_quotes = false;
	in_d_quotes = false;
	while (input[i])
	{
		if (input[i] == '\"' && !in_quotes)
			in_d_quotes = !in_d_quotes;
		if (input[i] == '\'' && !in_d_quotes)
			in_quotes = !in_quotes;
		if ((input[i] == '$' && input[i + 1] == '?') && !in_quotes)
		{
			size += exit_status_size() - 1;
			i += 1;
		}
		else if (input[i] == '$' && !in_quotes)
			size += expand_size(&(input[i]), &i, data) - 1;
		else
			i += 1;
		size += 1;
	}
	return (size);
}
