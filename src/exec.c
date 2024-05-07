/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/04/19 01:04:02 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	ft_unset(t_command *command, char **m_envp)
{
	int		i;

	i = 0;
	while (command->arg[i] != command->p_file)
		i++;
	while (command->arg[i] != NULL)
	{
		UNSET_Envp(m_envp, command->arg[i]);
		i++;
	}
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

	shlvl_envp = FIND_Var_Envp(m_envp, "SHLVL", 0);
	printf("cool la 1\n");

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

void	ft_executable(t_command *command, char **m_envp, int *wstatus)
{
	struct stat path_stat;
	int is_directory;

	shlvlup(m_envp);
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
			verif = EXPORT_Envp(m_envp, command->arg[i]);
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
	printf("exit\n");
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
		ft_free(command, NULL, m_envp, 1);//a voir pr la valeur de retour (jai mis un jsp comment tu fais avec 0)
	}
	return (0);
}

void	redir_output_append(t_command *command, char **m_envp, int *wstatus)
{
	int	fd;

	fd = open (command->right->cmd, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd < 0)
		exit(1);
	dup2(fd, STDOUT_FILENO);
	ft_exec(command->left, m_envp, wstatus);
}

void	redir_output(t_command *command, char **m_envp, int *wstatus)
{
	int	fd;

	fd = open(command->right->cmd, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		exit(1);
	dup2(fd, STDOUT_FILENO);
	ft_exec(command->left, m_envp, wstatus);
}

void	redir_input(t_command *command, char **m_envp, int *wstatus)
{
	int	fd;

	fd = open(command->right->cmd, O_RDONLY);
	if (fd < 0)
		exit(1);
	dup2(fd, STDIN_FILENO);
	ft_exec(command->left, m_envp, wstatus);
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

static int	match_path_count(char *command, char **path)
{
	int		i;
	char	*path_temp;

	i = 0;
	while (path[i])
	{
		path_temp = ft_strjoin(path[i], command);
		if (!path_temp)
			return (-1);
		i++;
		if (access(path_temp, X_OK) == 0)
		{
			free(path_temp);
			return (i);
		}
		free(path_temp);
	}
	return (0);
}

static char	**putlastslash(char **path)
{
	int		i;
	char	**path_temp;

	i = 0;
	while (path[i])
		i++;
	path_temp = malloc(sizeof(char *) * (i + 1));
	if (!path_temp)
		return (NULL);
	path_temp[0] = NULL;
	i = 0;
	while (path[i])
	{
		path_temp[i] = ft_strjoin(path[i], "/");
		if (path_temp[i] == NULL)
			return (NULL);
		i++;
	}
	path_temp[i] = NULL;
	return (path_temp);
}

char	*pathfinder(t_command *command, char **m_envp, int *flag)
{
	char	**path_list;
	char	**path_temp;
	char	*path;
	int		path_index;

	if (ft_strchr(command->cmd, '/'))
		return ((*flag)++, command->cmd);
	path_temp = ft_split((FIND_Var_Envp(m_envp, "PATH", 0) + 5), ':');
	if (!path_temp)
		return (NULL);
	path_list = putlastslash(path_temp);
	if (!path_list)
		return (NULL);
	path_index = match_path_count(command->cmd, path_list);
	if (path_index > 0)
	{
		path = ft_strjoin(path_list[path_index - 1], command->cmd);
		return (ft_free_double_tab(path_temp), \
				ft_free_double_tab(path_list), path);
	}
	ft_free_double_tab(path_temp);
	ft_free_double_tab(path_list);
	return (NULL);
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
