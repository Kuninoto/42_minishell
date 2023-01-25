/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:51:02 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/25 19:31:48 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_exit_status;

void	print_operator(t_operator operator)
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
}


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

char *expand(char *parsed, t_data *data)
{
	char	*var;

	if (parsed[1] == '?')
		return (ft_itoa(g_exit_status));
	var = getenv(&parsed[1]);
	if (var == NULL)
		var = get_fromvec(&parsed[1], &data->envp_vec);
	if (var == NULL)
		var = get_fromvec(&parsed[1], &data->var_vec);
	if (var == NULL)
		var = "";
	free(parsed);
	return (ft_strcpy(var));
}

size_t	get_token_len(char *input_at_i)
{
	size_t	i;

	i = 0;
	if (is_onstr(QUOTES, input_at_i[i]))
	{
		i += 1;
		while (input_at_i[i] && !is_onstr(QUOTES, input_at_i[i]))
			i += 1;
		return (i);
	}
	while (input_at_i[i] 
			&& !is_spaces(input_at_i[i]) 
			&& !is_onstr(QUOTES, input_at_i[i]))
	i += 1;
	return (i);
}

size_t	get_nr_statements(char *input)
{
	size_t	count;
	size_t	i;
	bool	flag;
	bool	has_quotes;

	count = 0;
	i = 0;
	flag = false;
	has_quotes = false;
	while (input[i])
	{
		if (is_onstr(QUOTES, input[i]))
			has_quotes = !has_quotes;
		if (input[i] != ' ' && !flag && !has_quotes)
		{
			flag = true;
			count += 1;
		}
		else if (input[i] == ' ')
			flag = false;
		i += 1;
	}
	return (count);
}

bool	check_quotes(char *input)
{
	int	s_quotes;
	int	d_quotes;
	int i;

	s_quotes = 0;
	d_quotes = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			s_quotes += 1;
		else if (input[i] == '\"')
			d_quotes += 1;
		i += 1;
	}
	if (s_quotes % 2 == 0 && d_quotes % 2 == 0)
		return (true);
	return (false);
}

char	**parse_input(char *input, t_data *data)
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
		if (len == 0)
		{
			i += 1;
			continue;
		}
		parsed[k] = malloc((len + 1) * sizeof(char));
		j = 0;
		while (input[i] && j < len)
		{
			if (is_onstr(QUOTES, input[i]))
				i += 1;
			else
				parsed[k][j++] = input[i++];
		}
		parsed[k][j] = '\0';
		if (is_onstr(parsed[k], '$') && !streq(parsed[k], "$"))
			parsed[k] = expand(parsed[k], data);
		k += 1;
	}
	parsed[k] = NULL;
	return (parsed);
}

t_statement	*parser(char *input, t_data *data)
{
	char		**parsed;
	t_statement	*temp;
	t_statement	*head;
	size_t		i;
	size_t		j;

	//parsed = ft_split(input, ' '); 
	if (!check_quotes(input))
		return (NULL);
	parsed = parse_input(input, data);
	temp = new_node(get_argc(&parsed[0]));
	head = temp;
	i = 0;
	while (parsed[i])
	{
		j = 0;
		while (parsed[i] && !is_onstr(OPERATORS, parsed[i][0]))
			temp->argv[j++] = parsed[i++];
		temp->argv[j] = NULL;
		if (!parsed[i])
			break ;
		temp->operator = get_operator(parsed[i++]);
		temp->next = new_node(get_argc(&parsed[i]));
		temp = temp->next;
	}
	temp->next = NULL;
	free(parsed);
	free(input);
	//debug_args(head);
	return (head);
}
