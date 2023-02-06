/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:02:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/06 18:58:50 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

char	*get_input(void)
{
	char	*raw_input;
	char	*input;

	raw_input = readline("minishell$ ");
	input = trim_free(raw_input, " \t");
	return (input);
}

void	wait_clean_parsed(t_statement *statement_list)
{
	wait(&g_exit_status);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	p_lstclear(statement_list);
}

int	lexer_string_size(char *input, t_data *data)
{
	size_t 	i;
	size_t 	size;
	size_t	var_size;
	char	*var_name;
	char	*var_value;
	bool	in_quotes;
	
	i = 0;
	size = 0;
	in_quotes = false;
	while(input[i])
	{
		if (input[i] == '\'')
			in_quotes = !in_quotes;
		if ((input[i] == '$' && input[i + 1] == '?') && !in_quotes)
		{
			i += 2;
			size += ft_strlen(ft_itoa(g_exit_status));
		}
		if (input[i] == '$' && !in_quotes)
		{
			var_size = 0;
			i += 1;
			while (input[i + var_size] && input[i + var_size] != ' ' && input[i + var_size] != '$')
				var_size += 1;
			var_name = ft_substr(input, i, var_size);
			var_value = get_fromvlst(var_name, &data->envp_lst);
			if(!var_value)
			{
				i += 1;
				continue;
			}
			size += ft_strlen(var_value);
			free(var_name);
			i += var_size;
			continue;
		}
		size += 1;
		i += 1;
	}
	return (size);
}

char *lexer(char *input, t_data *data)
{
	char	*expanded_input;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	size;
	char	*exit_status;
	char	*var_name;
	char	*var_value;
	bool	in_quotes;

	i = 0;
	j = 0;
	k = 0;
	size = 0;
	in_quotes = false;
	expanded_input = malloc((lexer_string_size(input, data) + 1)* sizeof(char));
	while (input[i])
	{
		if (input[i] == '\'')
			in_quotes = !in_quotes;
		if (input[i] == '$' && input[i + 1] == '?')
		{
			i += 2;
			exit_status = ft_itoa(g_exit_status);
			while (*exit_status)
				expanded_input[j++] = *exit_status++;
		}
		if (input[i] == '$' && !in_quotes)
		{
			size = 0;
			i += 1;
			k = 0;
			while (input[i + size] && input[i + size] != '$' && input[i + size] != ' ')
				size += 1;
			var_name = ft_substr(input, i, size);
			var_value = get_fromvlst(var_name, &data->envp_lst);
			while (var_value && var_value[k])
			{
				expanded_input[j] = var_value[k];
				j += 1;
				k += 1;	
			}
			free(var_name);
			i += size;
		}
		expanded_input[j] = input[i];
		i += 1;
		j += 1;
	}
	expanded_input[j] = '\0';
	free(input);
	return(expanded_input);
}

int	main(int ac, char **av, char **envp)
{
	t_data		data;
	t_statement	*statement_list;
	char		*input;

	if (av && ac > 1)
		panic(NULL, CL_ARGUMENTS_ERR, EXIT_FAILURE);
	setup_shell(envp, &data, &statement_list);
	while (1)
	{
		input = get_input();
		if (!valid_input(input, statement_list, &data) 
		|| input[0] == '\0')
			continue ;
		add_history(input);
		input = lexer(input, &data);
    // data.head = statement_list;
		statement_list = parser(input);
		exec_type(statement_list, &data);
		wait_clean_parsed(statement_list);
	}
	return (EXIT_SUCCESS);
}
