/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/23 23:53:19 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_echo(t_command *command)
{
	int		i;
	int		option;

	option = 0;
	i = 1;
	if (command->p_opt != NULL)
	{
		if (ft_strcmp(command->p_opt, "-n") == 0)
		{
			option = 1;
			i++;
		}
	}
	while (command->arg[i])
	{
		printf("%s", command->arg[i]);
		i++;
		if (command->arg[i])
			printf(" ");
	}
	if (option == 0)
		printf("\n");
}

void	ft_cd2(t_command *command, char **m_envp, int *wstatus)
{
	char	*home;

	home = FIND_Var_Envp(m_envp, "HOME", 0);
	if (home)
	{
		if (chdir(home) == 0)
			(*wstatus) = 0;
		else
		{
			(*wstatus) = 1;
			perror("minishell: cd");
		}
	}
	else
	{
		(*wstatus) = 1;
		printerr(2, command->cmd, "HOME not set", 1);
	}
}

void	ft_cd(t_command *command, char **m_envp, int *wstatus)
{
	int	i;

	i = 0;
	while (command->arg[i] != NULL)
		i++;
	if (i == 1 || i == 2)
	{
		if (command->p_file)
		{
			if (chdir(command->p_file) == 0)
				(*wstatus) = 0;
			else
			{
				(*wstatus) = 1;
				perror("minishell: cd");
			}
		}
		else
			ft_cd2(command, m_envp, wstatus);
	}
	else
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		(*wstatus) = 1;
	}
}

int	built_in(t_command *command, char **m_envp, int *wstatus)
{
	char	buffer[2048];

	if (!command->cmd)
		return (0);
	else if (ft_strcmp(command->cmd, "echo") == 0)
		return (ft_echo(command), 1);
	else if (ft_strcmp(command->cmd, "history") == 0)
		return (PRINT_History(), 1);
	else if (ft_strcmp(command->cmd, "env") == 0)
		return (ft_env(m_envp), 1);
	else if (ft_strcmp(command->cmd, "pwd") == 0)
	{
		getcwd(buffer, 2048);
		printf("%s\n", buffer);
		(*wstatus) = 0;
		ft_free(command, NULL, m_envp, 0);//a voir pr la valeur de retour (jai mis un jsp comment tu fais avec 0)
		exit(0);
	}
	return (0);
}
