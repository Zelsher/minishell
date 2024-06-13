/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/06/13 23:34:58 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_builtins(t_command *command, int *wstatus, char **m_envp)
{
	if (ft_strcmp(command->cmd, "cd") == 0)
		return (ft_cd(command, m_envp, wstatus), change_pwd(m_envp), 0);
	else if (ft_strcmp(command->cmd, "exit") == 0)
		return (ft_exit(command, m_envp, wstatus), 0);
	else if (ft_strcmp(command->cmd, "export") == 0)
		return (ft_export(command, m_envp, wstatus), 0);
	else if (ft_strcmp(command->cmd, "unset") == 0)
		return (ft_unset(command, m_envp, wstatus), 0);
	return (1);
}

int	pre_exec(t_command *command, char **m_envp, int *wstatus)
{
	int	pid;

	if (command->token != '|')
	{
		pid = fork();
		g_exec_pid = pid;
		if (pid == -1)
			ft_free(command, NULL, m_envp, 1);
		if (pid == 0)
			exec(command, m_envp, wstatus);
		wait_child(pid, wstatus);
	}
	else
		piper(command, m_envp, wstatus);
	if (*wstatus < 0 && *wstatus == 2)
		ft_free(command, NULL, m_envp, 1);
	if (g_exec_pid < 0)
		return (update_ctrlc(command, m_envp, wstatus), 1);
	else if (*wstatus == 131)
		return (update_ctrl_slash(command, m_envp, wstatus), 1);
	g_exec_pid = 0;
	if (!update_wstatus(m_envp, wstatus, 1))
		ft_free(command, NULL, m_envp, 1);
	return (ft_free(command, NULL, NULL, 0), 1);
}

void	use_command(t_mshell *m_shell, char *new_command,
	int *wstatus, char **m_envp)
{
	t_command	*command;
	int			verif;

	verif = 1;
	command = cmd_parse(m_shell, new_command, m_envp, wstatus);
	if (command && g_exec_pid == 0)
	{
		if (ft_builtins(command, wstatus, m_envp) != 0)
		{
			pre_exec(command, m_envp, wstatus);
			return ;
		}
		else
			verif = update_wstatus(m_envp, wstatus, 0);
	}
	else if (g_exec_pid < 0)
	{
		(*wstatus) = 130;
		verif = update_wstatus(m_envp, wstatus, 0);
	}
	ft_free(command, NULL, NULL, 0);
	if (!verif)
		ft_free(NULL, NULL, m_envp, 1);
}

int	minishell(t_mshell *m_shell, int *wstatus)
{
	while (1)
	{
		//printf("[%s]\n", m_shell->m_envp[0]);
		if (ft_atoi(m_shell->m_envp[0] + 3))
			m_shell->new_command = readline("\x1B[1;31mminishell:\x1B[0m");
		else
			m_shell->new_command = readline("\x1B[1;32mminishell:\x1B[0m");
		if (g_exec_pid < 0)
		{
			*wstatus = 130;
			if (!update_wstatus(m_shell->m_envp, wstatus, 0))
				ft_free(NULL, m_shell->new_command, m_shell->m_envp, 1);
			g_exec_pid = 0;
		}
		m_shell->line++;
		g_exec_pid = 0;
		if (!m_shell->new_command)
			return (printf ("exit\n"),
				ft_free(NULL, NULL, m_shell->m_envp, 0), exit(0), 1);
		if (m_shell->new_command[0] != 0 && !is_last_cmd(m_shell->new_command))
			add_history(m_shell->new_command);
		if (m_shell->new_command)
			use_command(m_shell, m_shell->new_command,
				wstatus, m_shell->m_envp);
	}
	return (1);
}
