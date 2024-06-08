/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/06/08 17:43:59 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	printerr(int fd, char *name, const char *error, int flag)
{
	if (flag == 1)
		write(fd, "minishell: ", 11);
	write(fd, name, ft_strlen(name));
	write(fd, ": ", 2);
	write(fd, error, ft_strlen(error));
	write(fd, "\n", 1);
}

void	error_command(t_command *command, char **m_envp, int *wstatus)
{
	printerr(2, command->cmd, ": command not found", 0);
	ft_free(command, NULL, m_envp, 0);
	exit (127);
	exit ((*wstatus));
}

void	ft_executable(t_command *command, char **m_envp, int *wstatus)
{
	struct stat	path_stat;

	execve(command->cmd, command->arg, m_envp);
	(*wstatus) = errno;
	stat(command->cmd, &path_stat);
	if (access(command->cmd, F_OK))
	{
		(*wstatus) = 127;
		printerr(2, command->cmd, "No such file or directory", 1);
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		(*wstatus) = 126;
		printerr(2, command->cmd, "Is a directory", 1);
	}
	else
	{
		(*wstatus) = 126;
		printerr(2, command->cmd, "Permission denied", 1);
	}
	exit ((*wstatus));
}

void	ft_do_command(t_command *command, char **m_envp, int *wstatus)
{
	int		flag;
	char	*path;

	flag = 0;
	path = pathfinder(command, m_envp, &flag);
	if (path)
		execve(path, command->arg, m_envp);
	else
		execve(command->cmd, command->arg, m_envp);
	printerr(2, command->cmd, "command not found", 0);
	if (flag == 0)
		free(path);
	ft_free(command, NULL, m_envp, 0);
	(*wstatus) = 127;
	exit ((*wstatus));
}

void	ft_exec(t_command *command, char **m_envp, int *wstatus)
{
	struct sigaction	sa;

	if (!init_child_signal(&sa))
		ft_free(command, NULL, m_envp, 1);
	else if (command->token == '<' || command->token == 'h')
		redir_input(command, m_envp, wstatus);
	else if (command->token == '>')
		redir_output(command, m_envp, wstatus);
	else if (command->token == 'r')
		redir_output_append(command, m_envp, wstatus);
	else if (built_in(command, m_envp, wstatus) == 1)
		ft_free(command, NULL, m_envp, (*wstatus));
	else if (command->cmd && ft_strchr(command->cmd, '/'))
		ft_executable(command, m_envp, wstatus);
	else if (command->token == 0)
		ft_do_command(command, m_envp, wstatus);
	else
	{
		printf("\n\nbizzare la\n\n");
		error_command(command, m_envp, wstatus);
	}
	exit ((*wstatus));
}
