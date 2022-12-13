/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:51:02 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/13 00:20:30 by nnuno-ca         ###   ########.fr       */
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

/* static size_t	get_table_len(char **splitted)
{
	size_t	counter;
	
	counter = 0;
	while ()
	{
		
		counter++;
	}
}

t_simple_command *parse_input(char *input)
{
	char	*temp;
	t_simple_command *table;

	temp = ft_split(input, ' ');
	table = malloc(get_table_len(temp) * sizeof(t_simple_command));

	

	return (table);
} */