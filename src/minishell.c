/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/06/13 16:57:54 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	update_wstatus(char **m_envp, int *wstatus, int flag)
{
	int		i;
	char	*char_wstatus;

	i = 0;
	char_wstatus = NULL;
	if (flag == 1)
		char_wstatus = ft_itoa(WEXITSTATUS(*wstatus));
	else if (flag == 0)
		char_wstatus = ft_itoa((*wstatus));
	if (!char_wstatus)
		return (0);
	while (char_wstatus[i])
	{
		m_envp[0][2 + i] = char_wstatus[i];
		i++;
	}
	m_envp[0][2 + i] = '\0';
	free(char_wstatus);
	*wstatus = 0;
	return (1);
}

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

void	update_ctrlc(t_command *command, char **m_envp, int *wstatus)
{
	if (*wstatus == -23)//trouver en cas dexecutable qui se termine pas a un ctrlc
		return ;
	(*wstatus) = 130;
	printf("\n");
	ft_free(command, NULL, NULL, 0);
	g_exec_pid = 0;
	if (!update_wstatus(m_envp, wstatus, 0))
		ft_free(command, NULL, m_envp, 1);
}

void	update_ctrl_slash(t_command *command, char **m_envp, int *wstatus)
{
	ft_free(command, NULL, NULL, 0);
	g_exec_pid = 0;
	printf("Quit(core dumped)\n");
	if (!update_wstatus(m_envp, wstatus, 0))
		ft_free(command, NULL, m_envp, 1);
}

int	pre_exec(t_command *command, char **m_envp, int *wstatus)
{
	int	pid;

	if (command->token !='|')
	{
		pid = fork();
		g_exec_pid = pid;
		if (pid == -1)
			ft_free(command, NULL, m_envp, 1);
		if (pid == 0)
			ft_exec(command, m_envp, wstatus);
		wait_child(pid, wstatus);
	}
	else
		piper(command, m_envp, wstatus);
	//printf("wstatus:%d\n", *wstatus);
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
		if (*wstatus)
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
