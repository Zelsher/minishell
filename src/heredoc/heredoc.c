/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:16:57 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/21 02:09:01 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	HEREDOC_Liner(char *reader, char **m_envp, int fd)
{
	char	*heredoc_line;
	
	if (!reader)
		return(0);
	heredoc_line = MALLOC_Heredoc_Line(reader, m_envp);
	if (heredoc_line)
	{
		CREATE_Heredoc_Line(reader, heredoc_line, m_envp);
		ft_putstr_fd(heredoc_line, fd);
		free(heredoc_line);
	}
	free(reader);
	return (0);
}

void	HEREDOCKER(char *delimiter, char **m_envp, int fd)
{
	char 	*reader;
	int		i;

	i = 0;
	while (1)
	{
		i++;
		reader = readline(">");
		if (!reader || !ft_strcmp(delimiter, reader))
		{
			if (!reader)
				ft_printf_error("minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", i + 1, delimiter);
			else 
				free(reader);
			break;
		}
		if (HEREDOC_Liner(reader, m_envp, fd))
			return ;
	}
}
char	*find_delimiter(char *new_command, t_parse *parse)
{
	char	*p_delimiter;

	parse->i = 0;
	while (is_in(new_command[parse->i], "\t\v\n\r ") && new_command[parse->i])
		parse->i++;
	p_delimiter = new_command + parse->i;
	while (!is_in(new_command[parse->i], "\t\v\n\r ") && new_command[parse->i])
		parse->i++;
	if (new_command[parse->i])
	{
		parse->i++;
		new_command[parse->i - 1] = '\0';
	}
	return (p_delimiter);
}

void	HEREDOC(t_command *command, char **m_envp, t_parse *parse, char *new_command)
{
	char		*delimiter;
	int 		fd;
	
	g_exec_pid = fork();
	if (g_exec_pid == -1)
		command->invalid = 1;
	if (g_exec_pid == 0)
	{
		g_exec_pid = -2;
		delimiter = find_delimiter(new_command, parse);
		fd = open(".temp_file", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    	if (fd == -1)
		{
			command->invalid = 1;
			return ;
		}
		HEREDOCKER(delimiter, m_envp, fd);
		close(fd);
		exit(0);
	}
	waitpid(g_exec_pid, NULL, 0);
	g_exec_pid = 0;
	parse->j += 2;
}
