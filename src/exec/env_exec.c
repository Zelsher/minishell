/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:58:11 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/26 20:46:27 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(char **m_envp)
{
	int	i;

	i = 1;
	while (m_envp[i] != NULL)
	{
		printf("%s\n", m_envp[i]);
		i++;
	}
}

void	ft_unset(t_command *command, char **m_envp)
{
	int		i;

	i = 0;
	while (command->arg[i] != command->p_file)
		i++;
	while (command->arg[i] != NULL)
	{
		unset_envp(m_envp, command->arg[i]);
		i++;
	}
}

void	ft_export(t_command *command, char **m_envp, int *wstatus)
{
	int		verif;
	int		i;
	char	flag;

	verif = 0;
	i = 1;
	flag = 0;
	if (command->arg[1] == command->p_file)
	{
		while (command->arg[i] != NULL)
		{
			verif = export_envp(m_envp, command->arg[i]);
			(*wstatus) = verif;
			if (verif != 0 && flag == 0)
			{
				(*wstatus) = 1;
				return ;
			}
			else
				flag += 1;
			i++;
		}
	}
	(*wstatus) = 0;
}

void	shlvlup2(char **m_envp, char *temp_num, int i)
{
	char	*shlvl_envp;

	shlvl_envp = ft_strjoin("SHLVL=", temp_num);
	if (!shlvl_envp)
	{
		free(temp_num);
		return ; 
	}
	m_envp[i] = shlvl_envp;
}

void	shlvlup(char **m_envp)
{
	char	*shlvl_envp;
	char	*temp_num;
	int		shlvl;
	int		i;

	shlvl_envp = find_var_envp(m_envp, "SHLVL", 0);
	if(!shlvl_envp)
		return ;
	i = 0;
	while(m_envp[i] != shlvl_envp)
		i++;
	shlvl = ft_atoi((shlvl_envp + 6));

	if (shlvl <= 0 || shlvl >= 1000)
		return ;
	shlvl += 1;

	if (shlvl == 1000)
		shlvl = 1;
	temp_num = ft_itoa(shlvl);

	if (!temp_num)
		return ; 
	free(shlvl_envp);
	shlvlup2(m_envp, temp_num, i);
}
