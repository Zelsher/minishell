/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/06/14 14:17:22 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_envp(char **m_envp)
{
	int	i;

	i = 0;
	if (!m_envp)
		return ;
	while (m_envp[i])
	{
		free(m_envp[i]);
		i++;
	}
}

void	free_single_command(t_command *command)
{
	int	i;

	i = 0;
	if (!command)
		return ;
	while (command->arg[i])
	{
		free(command->arg[i]);
		command->arg[i] = NULL;
		i++;
	}
	if (command->heredoc)
	{
		unlink(command->heredoc);
		free(command->heredoc);
	}
	free(command);
	return ;
}

void	free_command(t_command *command)
{
	int	i;

	i = 0;
	if (!command)
		return ;
	if (command->left)
		free_command(command->left);
	if (command->right)
		free_command(command->right);
	while (command->arg[i])
	{
		free(command->arg[i]);
		command->arg[i] = NULL;
		i++;
	}
	if (command->heredoc)
	{
		unlink(command->heredoc);
		free(command->heredoc);
	}
	free(command);
	return ;
}

void	ft_free(t_command *command, char *new_command,
	char **m_envp, int m_exit)
{
	free_command(command);
	ft_free_envp(m_envp);
	if (new_command)
	{
		free(new_command);
		new_command = NULL;
	}
	if (m_exit)
		exit(m_exit);
}
