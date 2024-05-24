/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/24 00:42:38 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exec_pid;

int	main(int argc, char **argv, char **envp)
{
	t_mshell			m_shell;
	char				*m_envp[1000];
	struct sigaction	sa;

	ENVP_Cpy(m_envp, envp);
	if (!INIT_Receive_Signal(&sa))
		return (ft_free(NULL, NULL, m_envp, 1), 1);
	m_shell.m_envp = m_envp;
	m_shell.command = NULL;
	m_shell.command = NULL;
	m_shell.line = 0;
	minishell(&m_shell);
	return (0);
	(void)argc;
	(void)argv;
}
