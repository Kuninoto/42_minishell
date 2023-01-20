/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:54:55 by roramos           #+#    #+#             */
/*   Updated: 2023/01/20 18:22:41 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dismiss_signal(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 1);
		write(STDOUT_FILENO, "\nminishell$ ", 12);
	}
}

void	config_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &dismiss_signal;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

/*	CTRL+C
		sigaction(SIGINT, &sa, NULL);
	Ignore CTRL+backslash
		signal(SIGQUIT, SIG_IGN);
*/