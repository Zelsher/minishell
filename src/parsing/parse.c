/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/06/08 17:39:06 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	redirect_init(t_command *command)
{
	t_command	*temp;
	int			i;

	i = 0;
	temp = command->right;
	while (command->left->arg[i])
		i++;
	if (i > 199)
		return (0);
	if (temp->token)
		temp = temp->left;
	command->left->arg[i] = strdup(temp->arg[0]);
	if (!command->left->arg[i])
		return (0);
	command->left->arg[i + 1] = NULL;
	return (1);
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
		if (!cmd->left || !cmd->right || !redirect_init(cmd))
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
		(*wstatus) = 2;
		if (!update_wstatus(m_envp, wstatus, 0))
			return (ft_free(command, NULL, m_envp, 1), NULL);
		return (free_command(command), NULL);
	}
	return (command);
}
