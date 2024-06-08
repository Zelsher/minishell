/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 21:37:05 by eboumaza          #+#    #+#             */
/*   Updated: 2024/06/08 17:22:50 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	wait_pid(int *pid, int *wstatus)
{
	int	i;

	i = 0;
	while (pid[i] != -1)
	{
		printf("Waiting for %d\n", pid[i]);
		waitpid(pid[i], wstatus, 0);
		i++;
	}
	printf("Stop wait\n");
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
