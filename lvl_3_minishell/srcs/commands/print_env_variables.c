/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 01:31:48 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/12 02:20:02 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env_variables(char *variable_name)
{
	char	*var_value;

	if (variable_name)
	{
		var_value = getenv(variable_name);
		if (var_value != NULL)
			printf("%s\n", var_value);
	}
}
