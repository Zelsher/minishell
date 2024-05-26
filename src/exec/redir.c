/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:59:54 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/24 16:08:28 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redir_output_append(t_command *command, char **m_envp, int *wstatus)
{
	int	fd;

	fd = open (command->right->cmd, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd < 0)
		exit(1);
	dup2(fd, STDOUT_FILENO);
	ft_exec(command->left, m_envp, wstatus);
}

void	redir_output(t_command *command, char **m_envp, int *wstatus)
{
	int	fd;

	fd = open(command->right->cmd, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		exit(1);
	dup2(fd, STDOUT_FILENO);
	ft_exec(command->left, m_envp, wstatus);
}

void	redir_input(t_command *command, char **m_envp, int *wstatus)
{
	int	fd;

	fd = open(command->right->cmd, O_RDONLY);
	if (fd < 0)
		ft_free(command, NULL, m_envp, 1);
	dup2(fd, STDIN_FILENO);
	ft_exec(command->left, m_envp, wstatus);
}

void	redir_heredoc(t_command *command, char **m_envp, int *wstatus)
{
	int	fd;

	fd = open(command->right->cmd, O_RDONLY);
	if (fd < 0)
		ft_free(command, NULL, m_envp, 1);
	dup2(fd, STDIN_FILENO);
	ft_exec(command->left, m_envp, wstatus);
}
