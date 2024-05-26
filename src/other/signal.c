/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/26 11:06:19 by eboumaza         ###   ########.fr       */
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
	if (g_exec_pid == 131)
		write (1, "Quit (core dumped)", 18);
	if (signal == SIGINT && g_exec_pid)
	{
		printf("\n");
		g_exec_pid = -5;
	}
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
