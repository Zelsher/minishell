/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 01:57:43 by eboumaza          #+#    #+#             */
/*   Updated: 2024/06/13 20:03:34 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mshell_signal_handler(int signal)
{
	if (signal == SIGINT && (!g_exec_pid || g_exec_pid == -2))
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_exec_pid = -2;
		return ;
	}
	if (signal == SIGINT && g_exec_pid > 0)
		g_exec_pid = -1;
}

void	child_signal_handler(int signal)
{
	if (signal == SIGQUIT)
		exit (131);
	if (signal == SIGINT)
		exit (130);
	(void)signal;
}

int	init_signal(int mod)
{
	struct sigaction	sa;

	if (mod == 0)
	{
		signal(SIGINT, SIG_IGN);
		sa.sa_handler = mshell_signal_handler;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		if (sigaction(SIGINT, &sa, NULL) == -1)
			return (0);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mod == 1 || mod == 2)
	{
		sa.sa_handler = child_signal_handler;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		if (sigaction(SIGINT, &sa, NULL) == -1)
			return (0);
		if (sigaction(SIGQUIT, &sa, NULL) == -1)
			return (0);
		if (mod == 2)
			signal(SIGQUIT, SIG_IGN);
	}
	return (1);
}
/*
static void	ctrl_c_action(void)
{
	g_current_status = 130;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	ctrl_s_action(void)
{
	g_current_status = 131;
	error_msg("Quit\n");
}

void	sig_main_handle(int signal)
{
	if (signal == SIGINT)
		ctrl_c_action();
}

void	sig_fork_handle(int signal)
{
	if (signal == SIGINT)
		ctrl_c_action();
	if (signal == SIGQUIT)
		ctrl_s_action();
}

void	sig_heredoc_handle(int signal)
{
	if (signal == SIGINT)
	{
		g_current_status = 130;
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	init_signal(int mod)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (mod == 0)
	{
		sa.sa_handler = sig_main_handle;
		signal(SIGQUIT, SIG_IGN);
	}
	if (mod == 1)
	{
		sa.sa_flags = SA_SIGINFO;
		sa.sa_handler = sig_fork_handle;
		sigaction(SIGQUIT, &sa, NULL);
	}
	if (mod == 2)
	{
		sa.sa_handler = sig_heredoc_handle;
		signal(SIGQUIT, SIG_IGN);
	}
	sigaction(SIGINT, &sa, NULL);
}

void	child(int sig)
{
	(void)sig;
	if (g_current_status == 2)
	{
		g_current_status = 130;
		write(1, "\n", 1);
	}
	if (g_current_status == 131)
		write(1, "Quit (core dumped)\n", 19);
}*/
