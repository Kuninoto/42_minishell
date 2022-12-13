/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:51:02 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/13 00:38:25 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

# define SYMBOLS "<|>&()";

int	get_token(char *line)
{
	if (line[0] == '<')
		return ('<');
	else if (line[0] == '|')
		return ('|');
	else if (line[0] == '>')
	{
		if (line[1] == '>')
			return ('+');
		else
			return ('>');
	}
	else if (line[0] == '&')
		return ('&');
	else if (line[0] == ')')
		return ('(');
	else if (line[0] == '(')
		return (')');
	else
		return ('a');
}

char	**parse_input(char *input)
{
	char	**splitted;
	size_t	i;

	splitted = ft_split(input, ' ');
	i = 0;
	while (splitted[i])
	{
		get_token(splitted[i]);
		i++;
	}
	return (splitted);
}


/*
	SHELL GRAMMAR

	cmd ::= text
*/