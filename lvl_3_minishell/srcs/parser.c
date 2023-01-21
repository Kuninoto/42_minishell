/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:51:02 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/20 22:11:37 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define debug_args for (int i = 0; i < head->argc; i += 1) \
						printf("%s -> ", head->argv[i]); \
				   printf("\n")

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
	if (streq(operator, "<<"))
		return (RDR_INPUT_UNTIL);
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
		counter += 1;
		i += 1;
	}
	return (counter);
}

char *is_var(char *splitted, t_data *data, int g_exit_status)
{
	bool	dollar;
	char	*var;

	dollar = ft_strchr(splitted, '$') != NULL;
	if (!dollar)
		return (splitted);
	if (dollar && splitted[1] == '?')
	{
		printf("exit_status = %d\n", g_exit_status);
		return (ft_itoa(g_exit_status));
	}
	var = getenv(++splitted);
	if (var == NULL)
		var = is_onvec(splitted, &data->envp_vec);
	if (var == NULL)
		var = is_onvec(splitted, &data->var_vec);
	return (ft_strcpy(var));
}

bool	has_quotes(char *line)
{
	int		dquotes;
	int		quotes;
	size_t	i;
	
	dquotes = 0;
	quotes = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			dquotes += 1;
		else if (line[i] == '\'')
			quotes += 1;
		i += 1;
	}
	if (dquotes == 2 || quotes == 2)
		return (true);
	else
		return (false);
}

t_statement	*parse_input(char *input, t_data *data, int g_exit_status)
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
			temp->argv[j++] = is_var(splitted[i++], data, g_exit_status);
		temp->argv[j] = NULL;
		if (!splitted[i])
			break ;
		temp->operator = get_operator(splitted[i++]);
		temp->next = new_node(get_nr_statements(&splitted[i]));
		temp = temp->next;
	}
	temp->next = NULL;
	free(splitted);
	free(input);
	debug_args;
	return (head);
}

/*
	ls -a | wc -l
	<command> <arguments> <operator> <command> <arguments>
*/