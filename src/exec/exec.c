/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/26 02:06:13 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	error_command(t_command *command, char **m_envp, int *wstatus)
{
	printerr(2, command->cmd, ": command not found", 0);
	ft_free(command, NULL, m_envp, 0);
	exit (127);
	exit ((*wstatus));
}

void	ft_executable(t_command *command, char **m_envp, int *wstatus)
{
	struct stat path_stat;
	int is_directory;

	//shlvlup(m_envp);
	execve(command->cmd, command->arg, m_envp);
	(*wstatus) = errno;
	stat(command->cmd, &path_stat);
	is_directory = S_ISDIR(path_stat.st_mode);
	if (is_directory != 0)
	{
		(*wstatus) = 126;
		printerr(2, command->cmd, "Is a directory\n", 1);
	}
	else
		perror("minishell");
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
	if (command->token == '|')
		pipecmd(command, m_envp, wstatus);
	else if (command->token == '<')
		redir_input(command, m_envp, wstatus);
	else if (command->token == '>')
		redir_output(command, m_envp, wstatus);
	else if (command->token == 'r')
		redir_output_append(command, m_envp, wstatus);
	else if (command->token == 'h')
		redir_heredoc(command, m_envp, wstatus);
	else if (built_in(command, m_envp, wstatus) == 1)
		ft_free(command, NULL, m_envp, (*wstatus));
	else if (command->cmd && command->cmd[0] == '.' && command->cmd[1] == '/' )
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
