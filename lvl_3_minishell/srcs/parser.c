/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:51:02 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/13 19:10:50 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

# define OPERATORS "<|>&()"

t_operator get_operator(char *operator)
{
	if (!operator)
		return (NONE);
	else if (ft_strncmp(operator, "&&", 2) == 0)
		return (AND);
	else if (ft_strncmp(operator, ">>", 2) == 0)
		return (REDIRECT_OUTPUT_APPEND);
	else if (ft_strncmp(operator, ">", 1) == 0)
		return (REDIRECT_OUTPUT_REPLACE);
	//TODO fazer o <<
	else if (ft_strncmp(operator, "<", 1) == 0)
		return (REDIRECT_INPUT);
	else if (ft_strncmp(operator, "||", 2) == 0)
		return (PIPE);
	else if (ft_strncmp(operator, "|", 1) == 0)
		return (OR);
	return (NONE);
	// TODO
/* 	else if (operator[0] == ')')
		return ('(');
	else if (operator[0] == '(')
		return (')'); */
}

size_t	get_nr_statements(char **splitted)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (splitted[i])
	{
		if (!ft_strchr(OPERATORS, splitted[i][0]))
			counter++;
		i++;
	}
	return (counter);
}

t_statement *parse_input(char *input)
{
	char		**splitted;
	size_t		nr_statements;
	size_t		i;
	t_statement	*temp;
	t_statement	*head;

	splitted = ft_split(input, ' ');
	nr_statements = get_nr_statements(splitted);
	i = 0;
	temp = new_node(nr_statements);
	head = temp;
	while (splitted[i])
	{
		temp->command = splitted[i++];
		if (!splitted[i][0])
			break ;
		while (splitted[i] && !ft_strchr(OPERATORS, splitted[i][0]))
		{
			temp->arguments[i] = splitted[i];
			i++;
		}
		temp->operator = get_operator(splitted[i++]);
		if (temp->operator == NONE)
			break ;
		temp->next = new_node(nr_statements);
		temp = temp->next;
	}
	temp->next = NULL;
	return (head);
}

/*
	ls -a | wc -l
	<command> <arguments> <operator> <command> <arguments>

	ls
	-a
	||
	wc
	-l
	NULL
*/