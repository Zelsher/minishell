/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:54:03 by eboumaza          #+#    #+#             */
/*   Updated: 2024/06/06 21:49:00 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	receive_pipe(t_command *command, int pipefd[2], char **m_envp, int *wstatus)
{

	t_command *p_command_pipe;

	p_command_pipe = command->right;
	ft_free(command->left, NULL, NULL, 0);
	free_single_command(command);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	ft_exec(p_command_pipe, m_envp, wstatus);
	close(pipefd[0]);
}

void	launch_pipe(t_command *command, int pipefd[2], char **m_envp, int *wstatus)
{
	t_command *p_command_pipe;

	p_command_pipe = command->left;
	ft_free(command->right, NULL, NULL, 0);
	free_single_command(command);
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	dup2(pipefd[1], STDERR_FILENO);
	ft_exec(p_command_pipe, m_envp, wstatus);
	close(pipefd[1]);
}

int	pipecmd(t_command *command, char **m_envp, int *wstatus)
{
	int	pipefd[2];
	int	p_id;

	if (pipe(pipefd) < 0)
		return (printerr(2, "minishell: ", "pipe has failed", 0), exit(1), 1);
	p_id = fork();
	if (p_id < 0)
		return (printerr(2, "minishell: ", "fork has failed", 0), exit(1), 1);
	if (p_id == 0)
		receive_pipe(command, pipefd, m_envp, wstatus);
	else
		launch_pipe(command, pipefd, m_envp, wstatus);
	return (1);
}
