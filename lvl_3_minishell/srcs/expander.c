/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:13:35 by roramos           #+#    #+#             */
/*   Updated: 2023/02/08 19:43:18 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static size_t	expand_exit_status(char *expanded_input_at_i)
{
	char	*exit_status;
	size_t	i;

	exit_status = ft_itoa(g_exit_status);
	i = 0;
	while (exit_status[i])
	{
		expanded_input_at_i[i] = exit_status[i];
		i += 1;
	}
	free(exit_status);
	return (i);
}

static size_t	exit_status_size(void)
{
	char	*exit_status;
	size_t	size;

	exit_status = ft_itoa(g_exit_status);
	size = ft_strlen(exit_status);
	free(exit_status);
	return (size);
}

static size_t	expand_size(char *input, size_t *i, t_data *data)
{
	size_t	var_size;
	char	*var_name;
	char	*var_value;

	var_size = 0;
	while (input[var_size]
		&& input[var_size] != ' '
		&& input[var_size] != '$')
				var_size += 1;
	var_name = ft_substr(input, *i, var_size);
	var_value = get_fromvlst(var_name, &data->envp_lst);
	if (!var_value)
		return (0);
	free(var_name);
	*i += var_size;
	return (ft_strlen(var_value));
}

int	expander_size(char *input, t_data *data)
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
		{
			in_quotes = !in_quotes;
			i += 1;
		}
		if ((input[i] == '$' && input[i + 1] == '?') && !in_quotes)
			size += exit_status_size() - 1;
		if (input[i] == '$' && !in_quotes)
			size += expand_size(&(input[i]), &i, data) - 1;
		i += 1;
		size += 1;
	}
	return (size);
}

char	*expander(char *input, t_data *data)
{
	char	*expanded_input;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	size;
	char	*var_name;
	char	*var_value;
	bool	in_quotes;

	i = 0;
	j = 0;
	in_quotes = false;
	expanded_input = malloc((expander_size(input, data) + 1) * sizeof(char));
	while (1)
	{
		if (input[i] == '\'')
			in_quotes = !in_quotes;
		if (input[i] == '$' && input[i + 1] == '?')
		{
			i += 2;
			j += expand_exit_status(&(expanded_input[j]));
		}
		if (input[i] == '$' && !in_quotes)
		{
			size = 0;
			i += 1;
			k = 0;
			while (input[i + size] && input[i + size] != '$' && input[i + size] != ' ')
				size += 1;
			var_name = ft_substr(input, i, size);
			var_value = get_fromvlst(var_name, &data->envp_lst);
			if (!var_value)
			{
				expanded_input[0] = '\0';
				continue ;
			}
			while (var_value[k])
				expanded_input[j++] = var_value[k++];
			free(var_name);
			i += size;
		}
		expanded_input[j++] = input[i++];
		if (expanded_input[j - 1] == '\0')
			break ;
	}
	free(input);
	return (expanded_input);
}
