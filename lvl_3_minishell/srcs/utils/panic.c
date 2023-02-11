/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 23:27:32 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/11 03:36:35 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	panic(t_data *data, char *error_msg, int exit_status)
{
	if (data)
		destroy(data);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	exit(exit_status);
}
