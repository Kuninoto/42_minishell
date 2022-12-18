/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 01:31:48 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/18 19:32:40 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env_variables(char *variable_name)
{
	char	*var_value;

	if (variable_name)
	{
	/* 	if (variable_name = '?')
			printf("");
		else
		{ */
			var_value = getenv(variable_name);
			if (var_value != NULL)
				printf("%s\n", var_value);
	//	}
	}
}
