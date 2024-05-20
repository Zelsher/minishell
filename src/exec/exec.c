/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/20 18:18:36 by eboumaza         ###   ########.fr       */
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

int	pipecmd(t_command *command, char **m_envp, int *wstatus)
{
	int	pipefd[2];
	int	p_id;

	if (pipe(pipefd) < 0)
		return (printerr(2, "minishell: ", "pipe has failed", 0), exit(1), 1);
	p_id = fork();
	if (p_id < 0)
		return (printerr(2, "minishell: ", "pipe has failed", 0), exit(1), 1);
	else if (p_id == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		ft_exec(command->right, m_envp, wstatus);
		close(pipefd[0]);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		ft_exec(command->left, m_envp, wstatus);
		close(pipefd[1]);
		waitpid(p_id, wstatus, 0);
	}
	return (0);
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
	g_exec_pid = -2;
	if (command->token == '|')
		pipecmd(command, m_envp, wstatus);
	else if (command->token == '<')
		redir_input(command, m_envp, wstatus);
	else if (command->token == '>')
		redir_output(command, m_envp, wstatus);
	else if (command->token == 'r')
		redir_output_append(command, m_envp, wstatus);
	else if (command->token == 'h')
		HEREDOC(command, m_envp, wstatus);
	else if (built_in(command, m_envp, wstatus) == 1)
		ft_free(command, NULL, m_envp, (*wstatus));
	else if (command->cmd[0] == '.' && command->cmd[1] == '/' )
		ft_executable(command, m_envp, wstatus);
	else if (command->token == 0)
		ft_do_command(command, m_envp, wstatus);
	else
	{
		printf("bizzare la\n\n\n");
		error_command(command, m_envp, wstatus);
	}
	exit ((*wstatus));
}
