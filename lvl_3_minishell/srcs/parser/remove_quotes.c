/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:19:32 by roramos           #+#    #+#             */
/*   Updated: 2023/02/22 17:03:45 by roramos          ###   ########.fr       */
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

static size_t	remove_quotes_size(char	*parsed)
{
	size_t	i;
	size_t	size;
	char	quotes;

	i = 0;
	size = 0;
	while (parsed[i])
	{
		while (parsed[i] && !is_onstr(QUOTES, parsed[i]))
		{
			i += 1;
			size += 1;
		}
		if (!parsed[i])
			break ;
		quotes = parsed[i++];
		while (parsed[i] && parsed[i] != quotes)
		{
			i += 1;
			size += 1;
		}
		quotes = 0;
	}
	return (size);
}

char	*remove_quotes(char	*parsed)
{
	size_t	i;
	size_t	j;
	char	quotes;
	char	*unquoted_parsed;

	i = 0;
	j = 0;
	quotes = '\0';
	unquoted_parsed = malloc((remove_quotes_size(parsed) + 1) * sizeof(char));
	while (parsed[i])
	{
		while (parsed[i] && !is_onstr(QUOTES, parsed[i]))
			unquoted_parsed[j++] = parsed[i++];
		if (!parsed[i])
			break ;
		quotes = parsed[i];
		i += 1;
		while (parsed[i] && parsed[i] != quotes)
			unquoted_parsed[j++] = parsed[i++];
		quotes = '\0';
	}
	unquoted_parsed[j] = '\0';
	free(parsed);
	return (unquoted_parsed);
}
