/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/06/11 01:42:20 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cmd_verifier(t_command *command, int *wstatus)
{
	int	verif;

	verif = 1;
	if (command->invalid)
	{
		(*wstatus) = 2;
		return (0);
	}
	else if ((!command->token && !command->cmd) || command->token == 'u')
		return (0);
	if (command->left)
		verif = cmd_verifier(command->left, wstatus);
	if (verif == 0)
		return (verif);
	if (command->right)
		verif = cmd_verifier(command->right, wstatus);
	if (verif == 0)
		return (verif);
	return (verif);
}

t_command	*recurs_parse(t_mshell *m_shell, char *new_command,
	int i, char token)
{
	t_command	*cmd;

	cmd = cmd_construct(m_shell, token);
	if (!cmd)
		return (NULL);
	if (tokener(new_command, cmd, &i, "|&"))
	{
		cmd->left = recurs_parse(m_shell, new_command, 0, cmd->token);
		cmd->right = recurs_parse(m_shell, new_command + i, 0, cmd->token);
		if (!cmd->left || !cmd->right)
			return (free_command(cmd), NULL);
	}
	if (tokener(new_command, cmd, &i, "<>"))
	{
		cmd->left = recurs_parse(m_shell, new_command, 0, '0');
		cmd->right = recurs_parse(m_shell, new_command + i, 0, cmd->token);
		if (!cmd->left || !cmd->right)
			return (free_command(cmd), NULL);
	}
	if (!cmd->token)
		cmd = cmd_filler(m_shell, new_command, cmd, token);
	return (cmd);
}

t_command	*cmd_parse(t_mshell *m_shell, char *new_command,
	char **m_envp, int *wstatus)
{
	t_command	*command;

	command = recurs_parse(m_shell, new_command, 0, 't');
	free(new_command);
	if (!command)
		ft_free(command, NULL, m_envp, 1);
	if (!cmd_verifier(command, wstatus))
	{
		if (!update_wstatus(m_envp, wstatus, 0))
			return (ft_free(command, NULL, m_envp, 1), NULL);
		return (free_command(command), NULL);
	}
	return (command);
}
