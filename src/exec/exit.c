/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:02:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/26 21:52:04 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit3(t_command *command, char **m_envp, int flag)
{
	char	c;
	int		i;

	i = 0;
	while (command->p_file[i] != '\0')
	{
		if (ft_isdigit(command->p_file[i]) != 1 && command->p_file[i] != '-' \
		&& command->p_file[i] != '+' && ft_iswspace(command->p_file[i]) != 1)
			flag += 1;
		i++;
	}
	if (flag == 0)
	{
		c = ft_atoi(command->p_file);
		ft_free(command, NULL, m_envp, c);
		exit(c);
	}
	else
		printerr(2, command->arg[1], "numeric argument required", 1);
}

void	ft_exit2(t_command *command, char **m_envp, int *wstatus, int i)
{
	int		flag;

	flag = 0;
	if (i == 1)
	{
		ft_free(command, NULL, m_envp, WEXITSTATUS((*wstatus)));
		exit((*wstatus));
	}
	else
		ft_exit3(command, m_envp, flag);
}

void	ft_exit(t_command *command, char **m_envp, int *wstatus)
{
	int				i;

	i = 0;
	while (command->arg[i] != NULL)
		i++;
	if (i == 1 || i == 2)
	{
		ft_exit2(command, m_envp, wstatus, i);
	}
	else
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		(*wstatus) = 1;
		return ;
	}
}
