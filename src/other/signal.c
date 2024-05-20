/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/04/19 00:48:33 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	SIGNAL_Handler(int signal)
{
	if (signal == SIGINT && g_exec_pid == -2)
		exit(130);
	else if (signal == SIGINT && (g_exec_pid == 0 || g_exec_pid == -1))
	{
		rl_replace_line("", 1);
		printf("\n$");
		rl_redisplay();
		g_exec_pid = -1;
		return;
	}
	if (signal == SIGINT && g_exec_pid)
		printf("\n");
}

int	INIT_Receive_Signal(struct sigaction *sa)
{
	sa->sa_handler = SIGNAL_Handler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	if (sigaction(SIGINT, sa, NULL) == -1)
		return (0);
	return (1);
}
