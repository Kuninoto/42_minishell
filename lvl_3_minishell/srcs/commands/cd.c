/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:20:58 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/12 00:39:11 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_cd(char *path)
{
	if (path == NULL)
		return ;
	if (chdir(path) == SUCESS)
		return ;
	perror("Failed to execute cd");
}
