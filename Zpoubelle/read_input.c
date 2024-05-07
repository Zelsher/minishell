/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 20:30:20 by eboumaza          #+#    #+#             */
/*   Updhated: 2024/04/13 23:41:53 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
int	send_input(int *wstatus, int *pipefd)
{
	char	*new_command;
	int		size;
	
	close(pipefd[0]);
	if (wstatus == 0)
		new_command = readline("\x1B[1;32m$\x1B[0m");
	else if (wstatus != 0)
		new_command = readline("\x1B[1;31m$\x1B[0m");
	if (!new_command)
		size = 0;
	else
		size = ft_strlen(new_command);
    if (write(pipefd[1], &size, sizeof(size)) == -1)
		return (close(pipefd[1]), free(new_command), exit(0), 0);
	if (write(pipefd[1], new_command, size) == -1)
		return (close(pipefd[1]), free(new_command), exit(0), 0);
	close(pipefd[1]);
	free(new_command);
	exit(0);
}

char	*receive_input(int child_pid, int *pipefd, char **m_envp)
{
	int		size;
	char	*new_command;

	g_exec_pid = child_pid;
	close(pipefd[1]);
	if (read(pipefd[0], &size, sizeof(size)) == -1 || !size)
		ft_free(NULL, NULL, m_envp, 1);
	if (!size)
		return (ft_free(NULL, NULL, m_envp, 1), NULL);
	new_command = malloc(sizeof(char) * size + 1);
	if (!new_command)
		ft_free(NULL, NULL, m_envp, 1);
	if (read(pipefd[0], new_command, size) == -1)
		ft_free(NULL, new_command, m_envp, 1);
	new_command[size] = '\0';
	waitpid(child_pid, NULL, 0);
	int dev_null = open("/dev/null", O_WRONLY);
    if (dev_null == -1) {
        perror("open");
    }
    if (dup2(dev_null, STDOUT_FILENO) == -1) {
        perror("dup2");
    }
    close(dev_null);
	if (g_exec_pid == -1)
		return (printf("\n"), free(new_command), NULL);
	g_exec_pid = 0;
	close(pipefd[0]);
	return (new_command);
}

char	*read_input(char **m_envp, int *wstatus)
{
	char	*new_command;
	pid_t	child_pid ;
    int 	pipefd[2];

    if (pipe(pipefd) == -1)
		ft_free(NULL, NULL, m_envp, 1);
	child_pid = fork();
	if (child_pid == -1)
		ft_free(NULL, NULL, m_envp, 1);
	if (child_pid != 0)
		new_command = receive_input(child_pid, pipefd, m_envp);
	else
		send_input(wstatus, pipefd);
	return (new_command);
}
#include "../inc/minishell.h"

int	send_input(int *wstatus, int *pipefd)
{
	char	*new_command;
	int		size;
	
	close(pipefd[0]);
	if (wstatus == 0)
		new_command = readline("\x1B[1;32m$\x1B[0m");
	else if (wstatus != 0)
		new_command = readline("\x1B[1;31m$\x1B[0m");
	if (!new_command)
		size = 0;
	else
		size = ft_strlen(new_command);
    if (write(pipefd[1], &size, sizeof(size)) == -1)
		return (close(pipefd[1]), free(new_command), exit(0), 0);
	if (write(pipefd[1], new_command, size) == -1)
		return (close(pipefd[1]), free(new_command), exit(0), 0);
	close(pipefd[1]);
	free(new_command);
	exit(0);
}

char	*receive_input(int child_pid, int *pipefd, char **m_envp)
{
	int		size;
	char	*new_command;

	g_exec_pid = child_pid;
	close(pipefd[1]);
	if (read(pipefd[0], &size, sizeof(size)) == -1 || !size)
		ft_free(NULL, NULL, m_envp, 1);
	if (!size)
		return (ft_free(NULL, NULL, m_envp, 1), NULL);
	new_command = malloc(sizeof(char) * size + 1);
	if (!new_command)
		ft_free(NULL, NULL, m_envp, 1);
	if (read(pipefd[0], new_command, size) == -1)
		ft_free(NULL, new_command, m_envp, 1);
	new_command[size] = '\0';
	waitpid(child_pid, NULL, 0);
	int dev_null = open("/dev/null", O_WRONLY);
    if (dev_null == -1) {
        perror("open");
    }
    if (dup2(dev_null, STDOUT_FILENO) == -1) {
        perror("dup2");
    }
    close(dev_null);
	if (g_exec_pid == -1)
		return (printf("\n"), free(new_command), NULL);
	g_exec_pid = 0;
	close(pipefd[0]);
	return (new_command);
}

char	*read_input(char **m_envp, int *wstatus)
{
	char	*new_command;
	pid_t	child_pid ;
    int 	pipefd[2];

    if (pipe(pipefd) == -1)
		ft_free(NULL, NULL, m_envp, 1);
	child_pid = fork();
	if (child_pid == -1)
		ft_free(NULL, NULL, m_envp, 1);
	if (child_pid != 0)
		new_command = receive_input(child_pid, pipefd, m_envp);
	else
		send_input(wstatus, pipefd);
	return (new_command);
}

int	main(int argc, char **argv, char **envp)
{
	char				*m_envp[1000];
	struct sigaction	sa;

	envp_cpy(m_envp, envp);
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (printf("Erreur lors de la définition du gestionnaire de signal")
			, ft_free(NULL, NULL, m_envp, 0), 1);
	minishell(m_envp);
	return (0);
	(void)argc;
	(void)argv;
}
