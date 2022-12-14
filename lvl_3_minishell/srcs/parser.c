/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:51:02 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/13 23:56:32 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

# define OPERATORS "|<>&()"

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
		return (OR);
	else if (ft_strncmp(operator, "|", 1) == 0)
		return (PIPE);
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
	while (splitted[i] && !ft_strchr(OPERATORS, splitted[i][0]))
	{
		counter++;
		i++;
	}
//	printf("counter = %ld\n", counter);
	return (counter);
}

t_statement *parse_input(char *input)
{
	char		**splitted;
	size_t		nr_statements;
	t_statement	*temp;
	t_statement	*head;
	size_t		i;
	size_t		j;

	splitted = ft_split(input, ' ');
	nr_statements = get_nr_statements(&splitted[0]);
	temp = new_node(nr_statements);
	head = temp;
	i = 0;
	while (splitted[i])
	{
		j = 0;
		temp->cmd = splitted[i];
		while (splitted[i] && !ft_strchr(OPERATORS, splitted[i][0]))
			temp->args[j++] = splitted[i++];
		temp->args[j] = NULL;
		if (!splitted[i])
			break ;
		temp->operator = get_operator(splitted[i++]);
		temp->next = new_node(get_nr_statements(&splitted[i]));
		temp = temp->next;
	}
	temp->next = NULL;
	free(splitted);
	return (head);
}
//!
//TODO
/*
	ls -a | wc -l
	operator pipe is not being assigned to ls structure
*/

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