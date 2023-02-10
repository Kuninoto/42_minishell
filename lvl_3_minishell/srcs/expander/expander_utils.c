/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:25:28 by roramos           #+#    #+#             */
/*   Updated: 2023/02/10 00:34:50 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

size_t	exit_status_size(void)
{
	char	*exit_status;
	size_t	size;

	exit_status = ft_itoa(g_exit_status);
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
	var_size = 0;
	while (input_at_i[var_size + 1]
		&& input_at_i[var_size + 1] != ' '
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

	i = 0;
	size = 0;
	in_quotes = false;
	while (input[i])
	{
		if (input[i] == '\'')
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
