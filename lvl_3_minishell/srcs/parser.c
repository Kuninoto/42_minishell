/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:51:02 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/18 19:30:06 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_operator	get_operator(char *operator)
{
	if (!operator)
		return (NONE);
	if (streq(operator, "|"))
		return (PIPE);
	if (streq(operator, "&&"))
		return (AND);
	if (streq(operator, ">>"))
		return (RDR_OUT_APPEND);
	if (streq(operator, ">"))
		return (RDR_OUT_REPLACE);
	/* if (streq(operator, "<<"))
		return (); */
	if (streq(operator, "<"))
		return (RDR_INPUT);
	if (streq(operator, "||"))
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
	while (splitted[i] && !ft_strchr(OPERATORS, splitted[i][0]))
	{
		counter++;
		i++;
	}
	return (counter);
}

char *is_var(char *splitted)
{
	char	*dollar;

	dollar = ft_strchr(splitted, '$');
	if (!dollar || splitted[1] == '?')
		return (splitted);
	return (join_freev2("", getenv(++splitted)));
}

t_statement	*parse_input(char *input)
{
	char		**splitted;
	t_statement	*temp;
	t_statement	*head;
	size_t		i;
	size_t		j;

	splitted = ft_split(input, ' ');
	temp = new_node(get_nr_statements(&splitted[0]));
	head = temp;
	i = 0;
	while (splitted[i])
	{
		j = 0;
		while (splitted[i] && !ft_strchr(OPERATORS, splitted[i][0]))
			temp->argv[j++] = is_var(splitted[i++]);
		temp->argv[j] = NULL;
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

/*
	ls -a | wc -l
	<command> <arguments> <operator> <command> <arguments>
*/