/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/06/14 14:57:23 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exec_pid;

void	envp_cpy(char **m_envp, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (envp[0][0] != '?')
	{
		m_envp[0] = malloc(sizeof(char) * 6);
		if (!m_envp[0])
			exit(1);
		ft_strcpy(m_envp[0], "?=0");
		j++;
	}
	while (envp[i] && j < 1000)
	{
		m_envp[j] = ft_strdup(envp[i]);
		if (!m_envp[i])
			ft_free(NULL, NULL, m_envp, 1);
		j++;
		i++;
	}
	m_envp[j] = NULL;
	if (!shlvlup(m_envp))
		ft_free(NULL, NULL, m_envp, 1);
}

int	fill_void_envp(char **m_envp)
{
	char	buffer[2048];

	printf("jfill\n");
	m_envp[0] = malloc(sizeof(char) * 6);
	if (!m_envp[0])
		exit(1);
	ft_strcpy(m_envp[0], "?=0");
	getcwd(buffer, 2048);
	m_envp[1] = ft_strjoin("PWD=", buffer);
	if (!m_envp[1])
		return (free(m_envp[0]), exit(1), 1);
	m_envp[2] = ft_strdup("SHLVL=1");
	if (!m_envp[2])
		return (free(m_envp[0]), free(m_envp[1]), exit(1), 1);
	m_envp[3] = ft_strdup("_=/usr/bin/env");
	if (!m_envp[3])
		return (free(m_envp[0]), free(m_envp[1]), free(m_envp[2]),
			exit(1), 1);
	m_envp[4] = NULL;
	printf("fin\n");
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_mshell			m_shell;
	char				*m_envp[1000];
	int					wstatus;

	wstatus = 0;
	if (argc != 1)
		return (printf("minishell: %s: no such file or directory\n", argv[1]),
			127);
	if (!envp[0])
		fill_void_envp(m_envp);
	else
		envp_cpy(m_envp, envp);
	init_signal(0);
	m_shell.m_envp = m_envp;
	m_shell.command = NULL;
	m_shell.command = NULL;
	m_shell.line = 0;
	minishell(&m_shell, &wstatus);
	return (0);
}
