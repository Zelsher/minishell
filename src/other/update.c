/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 23:32:19 by eboumaza          #+#    #+#             */
/*   Updated: 2024/06/14 14:18:07 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	update_wstatus(char **m_envp, int *wstatus, int flag)
{
	int		i;
	char	*char_wstatus;

	i = 0;
	char_wstatus = NULL;
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
	*wstatus = 0;
	return (1);
}

void	update_ctrlc(t_command *command, char **m_envp, int *wstatus)
{
	(*wstatus) = 130;
	printf("\n");
	ft_free(command, NULL, NULL, 0);
	g_exec_pid = 0;
	if (!update_wstatus(m_envp, wstatus, 0))
		ft_free(command, NULL, m_envp, 1);
}

void	update_ctrl_slash(t_command *command, char **m_envp, int *wstatus)
{
	ft_free(command, NULL, NULL, 0);
	g_exec_pid = 0;
	printf("Quit(core dumped)\n");
	if (!update_wstatus(m_envp, wstatus, 0))
		ft_free(command, NULL, m_envp, 1);
}
