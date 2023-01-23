/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:51:02 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/23 23:23:10 by nnuno-ca         ###   ########.fr       */
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
	// TODO
/* 	else if (operator[0] == ')')
		return ('(');
	else if (operator[0] == '(')
		return (')'); */
}

size_t	get_nr_args(char **parsed)
{
	size_t	i;

	i = 0;
	while (parsed[i] && !is_onstr(OPERATORS, parsed[i][0]))
		i += 1;
	printf("nr_args = %ld\n", i);
	return (i);
}

char *get_arg(char *field, t_data *data)
{
	bool	dollar;
	char	*var;

	dollar = is_onstr(field, '$');
	if (!dollar)
		return (field);
	if (dollar && field[1] == '?')
		return (ft_itoa(g_exit_status));
	var = getenv(&field[1]);
	if (var == NULL)
		var = is_onvec(&field[1], &data->envp_vec);
	if (var == NULL)
		var = is_onvec(&field[1], &data->var_vec);
	if (var == NULL)
		var = "";
	free(field);
	return (ft_strcpy(var));
}

size_t	get_token_len(char *input_at_i)
{
	size_t	i;

	i = 0;
	if (is_onstr(QUOTES, input_at_i[i]))
	{
		while (input_at_i[i] && !is_onstr(QUOTES, input_at_i[i]))
			i += 1;
	}
	else
	{
		while (input_at_i[i] 
				&& !is_spaces(input_at_i[i]) 
				&& !is_onstr(QUOTES, input_at_i[i])
				&& !is_onstr(OPERATORS, input_at_i[i]))
			i += 1;
	}
	return (i);
}

size_t	get_nr_statements(char *input)
{
	size_t	count;
	size_t	i;
	bool	flag;

	count = 0;
	i = 0;
	flag = false;
	while (input[i])
	{
		if (!is_onstr(DELIMS, input[i]) && flag == false)
		{
			flag = true;
			count += 1;
		}
		else if (is_onstr(DELIMS, input[i]))
			flag = false;
		i += 1;
	}
	printf("statements count = %ld\n", count);
	//exit(EXIT_SUCCESS);
	return (count);
}

char	**parse_input(char *input)
{
	size_t		i;
	size_t		k;
	size_t		j;
	bool		has_quotes;
	char		**parsed;
	size_t		len;

	i = 0;
	has_quotes = false;
	parsed = malloc(get_nr_statements(input) + 1);
	/* ls -la | wc -l */
	k = 0;
	while (input[i])
	{
		len = get_token_len(&input[i]);
		printf("len = %ld\n", len);
		parsed[k] = malloc((len + 1) * sizeof(char));
		j = 0;
		while (j < len)
		{
			if (is_onstr(QUOTES, input[i]))
			{
				has_quotes = !has_quotes;
				i += 1;
			}
			if (is_onstr(OPERATORS, input[i]) && !has_quotes)
				parsed[k][j++] = input[i++];
			if (input[i] == ' ' && !has_quotes)
			{
				i += 1;
				break ;
			}
			parsed[k][j++] = input[i++];
		}
		printf("input index = %ld\n", i);
		parsed[k][j] = '\0';
		printf("token = %s\n", parsed[k]);
		k += 1;
	}
	parsed[k] = NULL;
	return (parsed);
}


/* A cada espaço ou operador ou EOF é mais um espaco */
t_statement	*parser(char *input, t_data *data)
{
	char		**parsed;
	t_statement	*temp;
	t_statement	*head;
	size_t		i;
	size_t		j;

	//splitted = ft_split(input, ' '); 
	parsed = parse_input(input);
	temp = new_node(get_nr_args(&parsed[0]));
	head = temp;
	i = 0;
	while (parsed[i])
	{
		j = 0;
		while (parsed[i] && !is_onstr(OPERATORS, parsed[i][0]))
			temp->argv[j++] = get_arg(parsed[i++], data);
		temp->argv[j] = NULL;
		if (!parsed[i])
			break ;
		temp->operator = get_operator(parsed[i++]);
		temp->next = new_node(get_nr_args(&parsed[i]));
		temp = temp->next;
	}
	temp->next = NULL;
	free(parsed);
	free(input);
	debug_args(head);
	return (head);
}

/*
	ls -a | wc -l
	<command> <arguments> <operator> <command> <arguments>
*/
