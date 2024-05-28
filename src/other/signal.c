/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/28 02:04:39 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	signal_handler(int signal)
{
	if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (signal == SIGINT && (!g_exec_pid || g_exec_pid == -1))
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_exec_pid = -1;
		return ;
	}
	else if (signal == SIGINT && g_exec_pid)
		g_exec_pid = -2;
}

void	child_signal_handler(int signal)
{
	if (signal == SIGINT && g_exec_pid == 0)
		exit(130);
}

int	init_receive_signal(struct sigaction *sa)
{
	sa->sa_handler = signal_handler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	if (sigaction(SIGINT, sa, NULL) == -1)
		return (0);
	if (sigaction(SIGQUIT, sa, NULL) == -1)
		return (0);
	return (1);
}

int	init_child_signal(struct sigaction *sa)
{
	sa->sa_handler = child_signal_handler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	if (sigaction(SIGINT, sa, NULL) == -1)
		return (0);
	if (sigaction(SIGQUIT, sa, NULL) == -1)
		return (0);
	return (1);
}
