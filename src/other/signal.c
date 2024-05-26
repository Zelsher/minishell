/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/26 18:56:13 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	SIGNAL_Handler(int signal)
{
	if (signal == SIGINT && (!g_exec_pid || g_exec_pid == -1))
	{
		rl_replace_line("", 1);
		printf("\x1B[1;31m\n$\x1B[0m");
		rl_redisplay();
		g_exec_pid = -1;
		return;
	}
	else if (signal == SIGINT && g_exec_pid)
	{
		printf("\n");
		g_exec_pid = signal * -1;
	}
}

int	INIT_Receive_Signal(struct sigaction *sa)
{
	sa->sa_handler = SIGNAL_Handler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	if (sigaction(SIGINT, sa, NULL) == -1)
		return (0);
	if (sigaction(SIGQUIT, sa, NULL) == -1)
		return (0);
	return (1);
}
