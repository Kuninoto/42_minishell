/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:02:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/29 18:22:38 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*//TODO 
	handle "", parsing should recognize that the text between
	dquotes is only 1 argument and trim them
exit with 1 paramater*/
char	*get_readline(void)
{
	char	*raw_input;
	char	*input;

	raw_input = readline("$ ");
	input = ft_strtrim(raw_input, " \t");
	free(raw_input);
	return (input);
}

void	setup_shell(int ac, char **av, t_vector *vv, t_vector *ev)
{
	(void)ac;
	(void)av;
	*vv = vec_new();
	*ev = vec_new();
	config_signals();
	welcome_art();
}

int	main(int argc, char **argv, char **envp)
{
	t_vector	var_vec;
	t_vector	envp_vec;
	int			exit_status;
	char		*input;
	t_statement	*statement_list;

	exit_status = 0;
	setup_shell(argc, argv, &var_vec, &envp_vec);
	while (1)
	{
		input = get_readline();
		if (input == NULL || streq(input, "exit"))
			cmd_exit(input == NULL, &var_vec, &envp_vec);
		if (input[0] == '\0')
			continue ;
		add_history(input);
		statement_list = parse_input(input, &var_vec, &envp_vec, exit_status);
		free(input);
		exec_type(statement_list, envp, &envp_vec, &var_vec);
		wait(&exit_status);
		if (WIFEXITED(exit_status))
			exit_status = WEXITSTATUS(exit_status);
		lstclear(&statement_list);
	}
	return (EXIT_SUCCESS);
}
