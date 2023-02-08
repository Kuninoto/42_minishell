/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:51:02 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/08 19:35:13 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

/* void	print_operator(t_operator operator)
{
	const char *operators[6] = {"NONE", ">", ">>", "<", "<<", "|"};
	printf("OPERATOR = %s", operators[operator]);
}

void	debug_args(t_statement *head)
{
	for (t_statement *temp = head; temp != NULL; temp = temp->next)
	{
		printf("ARGC = %d\n", temp->argc);
		printf("ARGV = ");
		for (int i = 0; i < temp->argc; i += 1)
			printf("%s -> ", temp->argv[i]);
		printf("\n");
		print_operator(temp->operator);
		printf("\n\n");
	}
	printf("OUTPUT: \n");
} */

t_operator	get_operator(char *operator)
{
	if (!operator)
		return (NONE);
	if (streq(operator, "|"))
		return (PIPE);
	if (streq(operator, ">>"))
		return (RDR_OUT_APPEND);
	if (streq(operator, ">"))
		return (RDR_OUT_REPLACE);
	if (streq(operator, "<<"))
		return (RDR_INPUT_UNTIL);
	if (streq(operator, "<"))
		return (RDR_INPUT);
	return (NONE);
}

size_t	get_argc(char **parsed)
{
	size_t	i;

	i = 0;
	while (parsed[i])
		i += 1;
	return (i);
}

size_t	get_token_len(char *input_at_i)
{
	size_t	i;
	char	quotes;

	i = 0;
	if (is_onstr(REDIRECTS, input_at_i[i]))
	{
		if (input_at_i[i] == input_at_i[i + 1])
			return (2);
		return (1);
	}
	while (input_at_i[i] && !is_spaces(input_at_i[i]))
	{
		if (is_onstr(QUOTES, input_at_i[i]))
		{
			quotes = input_at_i[i++];
			while (input_at_i[i] && input_at_i[i] != quotes)
				i += 1;
		}
		i += 1;
	}
	return (i);
}

size_t	get_nr_statements(char *input)
{
	size_t	count;
	bool	flag;
	bool	has_quotes;

	count = 0;
	flag = false;
	has_quotes = false;
	while (*input)
	{
		if (is_onstr(REDIRECTS, *input))
			count += 1;
		if (is_onstr(QUOTES, *input))
		{
			if (*input == *(input + 1))
				input += 2;
			else
				has_quotes = !has_quotes;
		}
		if (*input != ' ' && !flag && !has_quotes)
		{
			flag = true;
			count += 1;
		}
		else if (*input == ' ')
			flag = false;
		input += 1;
	}
	return (count);
}

char	**parse_input(char *input)
{
	size_t		i;
	size_t		k;
	char		**parsed;
	size_t		len;
	size_t		j;

	i = 0;
	k = 0;
	parsed = malloc((get_nr_statements(input) + 1) * sizeof(char *));
	while (input[i])
	{
		len = get_token_len(&input[i]);
		if (!len)
		{
			i += 1;
			continue ;
		}
		parsed[k] = malloc((len + 1) * sizeof(char));
		j = 0;
		while (input[i] && j < len)
			parsed[k][j++] = input[i++];
		parsed[k++][j] = '\0';
	}
	parsed[k] = NULL;
	return (parsed);
}

t_statement	*parser(char *input)
{
	char		**parsed;
	t_statement	*temp;
	t_statement	*head;
	size_t		idx[2];

	parsed = parse_input(input);
	temp = p_new_node(get_argc(&parsed[0]));
	head = temp;
	idx[0] = 0;
	while (parsed[idx[0]])
	{
		idx[1] = 0;
		while (parsed[idx[0]] && !is_onstr(OPERATORS, parsed[idx[0]][0]))
			temp->argv[idx[1]++] = remove_quotes(parsed[idx[0]++]);
		temp->argv[idx[1]] = NULL;
		if (!parsed[idx[0]])
			break ;
		temp->operator = get_operator(parsed[idx[0]++]);
		temp->next = p_new_node(get_argc(&parsed[idx[1]]));
		temp = temp->next;
	}
	temp->next = NULL;
	free(parsed);
	return (head);
}
