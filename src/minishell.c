/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/26 17:54:52 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	UPDATE_Wstatus(char **m_envp, int *wstatus, int flag)
{
	int	i;
	char	*char_wstatus;

	i = 0;
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
	return (1);
}

int	ft_builtins(t_command *command, int *wstatus, char **m_envp)
{
	if(ft_strcmp(command->cmd, "cd") == 0)
		return(ft_cd(command, m_envp, wstatus), 0);
	else if (ft_strcmp(command->cmd, "exit") == 0)
		return (ft_exit(command, m_envp, wstatus), 0); 
	else if (ft_strcmp(command->cmd, "export") == 0)
		return (ft_export(command, m_envp, wstatus), 0);
	else if (ft_strcmp(command->cmd, "unset") == 0)
		return (ft_unset(command, m_envp), 0);
	return (1);
}

void	USE_Command(t_mshell *m_shell, char *new_command, int *wstatus, char **m_envp)
{
	t_command	*command;
	int			verif;

	verif = 0;
	command = CMD_Parse(m_shell, new_command, m_envp, wstatus);
	print_cmd(command, 0);
	if (command && g_exec_pid != -1)
	{
		if(ft_builtins(command, wstatus, m_envp) != 0)
		{
			g_exec_pid = fork();
			if (g_exec_pid == -1)
				ft_free(command, NULL, m_envp, 1);
			if (g_exec_pid == 0)
				ft_exec(command, m_envp, wstatus);
			waitpid(g_exec_pid, wstatus, 0);
			if (g_exec_pid == -5)
			{
				(*wstatus) = 130;
				printf("\n");
				UPDATE_Wstatus(m_envp, wstatus, 0);
				return;
			}
			g_exec_pid = 0;
			ft_free(command, NULL, NULL, 0);
			verif = UPDATE_Wstatus(m_envp, wstatus, 1);
		}
		else
			verif = UPDATE_Wstatus(m_envp, wstatus, 0);
		if (!verif)
			ft_free(command, NULL, m_envp, 1);
	}
}

void	minishell(t_mshell *m_shell)
{
	char				*new_command;
	int					wstatus;

	wstatus = 0;
	while (1)
	{
		if (wstatus)
			new_command = readline("\x1B[1;31m$\x1B[0m");
		else
			new_command = readline("\x1B[1;32m$\x1B[0m");
		m_shell->line++;
		g_exec_pid = 0;
		if (!new_command)
			ft_free(NULL, NULL, m_shell->m_envp, 1);
		if (new_command[0] != 0 && !IS_Last_Cmd(new_command))
			add_history(new_command);
		m_shell->new_command = new_command;
		if (new_command)
			USE_Command(m_shell, new_command, &wstatus, m_shell->m_envp);
	}
}
