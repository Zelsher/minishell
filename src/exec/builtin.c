/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/06/14 14:05:32 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	change_pwd(char **m_envp)
{
	char	*tmp;
	char	*pwd;

	unset_envp(m_envp, "OLDPWD");
	tmp = find_var_envp(m_envp, "PWD", 0);
	if (!tmp)
		return (0);
	pwd = ft_strjoin("OLDPWD=", tmp);
	if (!pwd)
		return (0);
	export_envp(m_envp, pwd);
	free(pwd);
	unset_envp(m_envp, "PWD");
	tmp = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", tmp);
	if (!pwd)
		return (free(tmp), 0);
	free(tmp);
	export_envp(m_envp, pwd);
	free(pwd);
	return (0);
}

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

	home = find_var_envp(m_envp, "HOME", 0);
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
	if (ft_strcmp(command->cmd, "cd") == 0)
		return (ft_cd(command, m_envp, wstatus), change_pwd(m_envp), 1);
	else if (ft_strcmp(command->cmd, "echo") == 0)
		return (ft_echo(command), 1);
	else if (ft_strcmp(command->cmd, "history") == 0)
		return (print_history(), 1);
	else if (ft_strcmp(command->cmd, "env") == 0)
		return (ft_env(m_envp), 1);
	else if (ft_strcmp(command->cmd, "exit") == 0)
		return (ft_exit(command, m_envp, wstatus), 1);
	else if (ft_strcmp(command->cmd, "pwd") == 0)
	{
		getcwd(buffer, 2048);
		printf("%s\n", buffer);
		(*wstatus) = 0;
		ft_free(command, NULL, m_envp, 0);
		exit(0);
	}
	return (0);
}
