/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:59:54 by eboumaza          #+#    #+#             */
/*   Updated: 2024/06/08 22:03:57 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*last_arg(t_command *command)
{
	int	i;

	i = 0;
	if (command->token)
	command = command->left;
	while (command->arg[i + 1])
		i++;
	return (command->arg[i]);
}

void	redir_output_append(t_command *command, char **m_envp, int *wstatus)
{
	int	fd;

	fd = open (last_arg(command->right), O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd < 0)
		exit(1);
	dup2(fd, STDOUT_FILENO);
	ft_exec(command->left, m_envp, wstatus);
}

void	redir_output(t_command *command, char **m_envp, int *wstatus)
{
	int	fd;

	fd = open(last_arg(command->right), O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		exit(1);
	dup2(fd, STDOUT_FILENO);
	ft_exec(command->left, m_envp, wstatus);
}

void	redir_input(t_command *command, char **m_envp, int *wstatus)
{
	int	fd;

	fd = open(last_arg(command->right), O_RDONLY);
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
