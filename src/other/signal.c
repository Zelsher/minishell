/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/06/11 02:13:38 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	mshell_signal_handler(int signal)
{
	//printf("parent %d recoie %d\n", getpid(), signal);
	if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (signal == SIGINT && (!g_exec_pid))
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		return ;
	}
}

void	child_signal_handler(int signal)
{
	printf("child %d recoie %d\n", getpid(), signal);
	(void)signal;
}

int	init_signal(int mod)
{
	struct sigaction sa;

	if (mod == 0)
	{
		sa.sa_handler = mshell_signal_handler;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
	}
	else if (mod == 1)
	{
		sa.sa_handler = child_signal_handler;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
	}
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (0);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
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
