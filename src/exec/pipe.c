/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:54:03 by eboumaza          #+#    #+#             */
/*   Updated: 2024/06/08 17:47:28 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	launch_pipe(t_command *command, t_piper *piper,
	char **m_envp, int *wstatus)
{
	t_command	*p_command_pipe;

	free(piper->pid);
	piper->new_pipe[0] = -1;
	piper->new_pipe[2] = -1;
	p_command_pipe = command->left;
	ft_free(command->right, NULL, NULL, 0);
	free_single_command(command);
	close(piper->pipe[0]);
	dup2(piper->pipe[1], STDOUT_FILENO);
	dup2(piper->pipe[1], STDERR_FILENO);
	ft_exec(p_command_pipe, m_envp, wstatus);
	exit(*wstatus);
}

void	receive_pipe(t_command *command, t_piper *piper,
	char **m_envp, int *wstatus)
{
	t_command	*p_command_pipe;

	free(piper->pid);
	p_command_pipe = command->left;
	ft_free(command->right, NULL, NULL, 0);
	free_single_command(command);
	close(piper->pipe[1]);
	close(piper->new_pipe[0]);
	dup2(piper->pipe[0], STDIN_FILENO);
	dup2(piper->new_pipe[1], STDOUT_FILENO);
	dup2(piper->new_pipe[1], STDERR_FILENO);
	ft_exec(p_command_pipe, m_envp, wstatus);
	exit(*wstatus);
}

void	close_pipe(t_command *command, t_piper *piper,
	char **m_envp, int *wstatus)
{
	free(piper->pid);
	close(piper->pipe[1]);
	close(piper->new_pipe[0]);
	dup2(piper->pipe[0], STDIN_FILENO);
	ft_exec(command, m_envp, wstatus);
	exit(*wstatus);
}

int	pipe_manager(t_command *command, t_piper *piper,
	char **m_envp, int *wstatus)
{
	piper->pid[piper->i] = fork();
	if (piper->pid[piper->i] == -1)
		return (free(piper->pid), ft_free(command, NULL, m_envp, -1), 1);
	else if (piper->pid[piper->i] == 0 && piper->i == 0)
		launch_pipe(command, piper, m_envp, wstatus);
	else if (piper->pid[piper->i] == 0 && command->right
		&& command->right->token == '|')
		receive_pipe(command, piper, m_envp, wstatus);
	else if (piper->pid[piper->i] == 0 && command->token != '|')
		close_pipe(command, piper, m_envp, wstatus);
	if (piper->i != 0 && (!command->right || command->right->token != '|'))
		return (0);
	piper->i++;
	if (piper->i != 1)
		piper->pipe[0] = piper->new_pipe[0];
	if (pipe(piper->new_pipe) < 0)
		return (printerr(2, "minishell: ", " pipe has failed", 0),
			ft_free(command, NULL, m_envp, 1), 1);
	return (1);
}

int	piper(t_command *command, char **m_envp, int *wstatus)
{
	t_command	*p_command;
	t_piper		piper;

	p_command = command;
	piper.pid = NULL;
	piper.i = 0;
	if (command->token != '|')
		ft_exec(command, m_envp, wstatus);
	if (pipe(piper.pipe) < 0)
		return (printerr(2, "minishell: ", " pipe has failed", 0),
			ft_free(command, NULL, m_envp, -1), 1);
	while (1)
	{
		piper.pid = create_new_pid_list(&piper);
		if (!piper.pid)
			return (0);
		if (!pipe_manager(command, &piper, m_envp, wstatus))
			break ;
		ft_free(command->left, NULL, NULL, 0);
		p_command = command->right;
		free_single_command(command);
		command = p_command;
	}
	return (wait_pid(piper.pid, wstatus), free(piper.pid),
		ft_free(command, NULL, m_envp, 0), exit(*wstatus), 0);
}
