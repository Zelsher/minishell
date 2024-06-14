/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:02:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/06/14 14:14:45 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit(t_command *command, char **m_envp, int *wstatus)
{
	printf("exit\n");
	if (command->arg[1] && ft_is_str_num(command->arg[1]) && !command->arg[2])
		ft_free(command, NULL, m_envp, ft_atoi(command->arg[1]));
	else if (ft_is_str_num(command->arg[1]) && command->arg[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		ft_free(command, NULL, m_envp, 0);
		(*wstatus) = 1;
	}
	else if (!ft_is_str_num(command->arg[1]))
	{
		ft_printf_error("minishell: exit: %s: numeric argument required\n",
			command->arg[1]);
		ft_free(command, NULL, m_envp, 2);
	}
	else
	{
		ft_free(command, NULL, m_envp, 0);
		exit(0);
	}
	(void)wstatus;
}
