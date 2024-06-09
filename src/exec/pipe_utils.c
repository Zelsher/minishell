/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 21:37:05 by eboumaza          #+#    #+#             */
/*   Updated: 2024/06/10 01:41:58 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	wait_pid(int *pid, int *wstatus)
{
	int	i;

	i = 0;
	while (pid[i] != -1)
	{
		waitpid(pid[i], wstatus, 0);
		i++;
	}
}

int	*create_new_pid_list(t_piper *piper)
{
	int	i;
	int	*new_pid;

	new_pid = malloc(sizeof(int) * (piper->i + 2));
	if (!new_pid)
		return (NULL);
	if (!piper->pid)
	{
		new_pid[1] = -1;
		return (new_pid);
	}
	i = 0;
	while (piper->pid[i] != -1)
	{
		new_pid[i] = piper->pid[i];
		i++;
	}
	new_pid[i + 1] = -1;
	free(piper->pid);
	return (new_pid);
}

void	end_pipe(t_command *command, char **m_envp,
	t_piper *piper, int *wstatus)
{
	close(piper->pipe[0]);
	close(piper->pipe[1]);
	if (piper->new_pipe[0] != -1)
		close(piper->new_pipe[0]);
	if (piper->new_pipe[1] != -1)
		close(piper->new_pipe[1]);
	wait_pid(piper->pid, wstatus);
	free(piper->pid);
	ft_free(command, NULL, m_envp, 0);
	exit(*wstatus);
}
