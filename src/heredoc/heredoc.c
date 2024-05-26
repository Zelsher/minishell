/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:16:57 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/26 20:39:55 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*heredoc_liner(char *reader, char **m_envp, int fd)
{
	char	*heredoc_line;
	
	if (!reader)
		return(NULL);
	heredoc_line = malloc_heredoc_line(reader, m_envp);
	if (heredoc_line)
	{
		create_heredoc_line(reader, heredoc_line, m_envp);
		ft_putstr_fd(heredoc_line, fd);
		free(heredoc_line);
		//free(reader);
	}
	free(reader);
	return (NULL);
}

int	heredocker(t_mshell *m_shell, char *file_name, char *delimiter)
{
	char 	*reader;
	int		line;
	int		fd;
	
	line = 0;
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (free(file_name), -1);
	while (1)
	{
		reader = readline(">");
		if (!reader || !ft_strcmp(delimiter, reader))
		{
			if (!reader)
				ft_printf_error(HEREDOC_EOF, m_shell->line, delimiter);
			else 
				free(reader);
			m_shell += line;
			break;
		}
		heredoc_liner(reader, m_shell->m_envp, fd);
		line++;
	}
	close(fd);
	return (free(file_name), 1);
}

int	heredoc(t_mshell *m_shell, t_command *command, t_parse *parse, char *new_command)
{
	static size_t	count;
	char			*delimiter;
	int				verif;
	char			*file_name;
	
	delimiter = find_delimiter(new_command, parse);
	file_name = generate_file(&count);
	if (!file_name)
		return (return_parse_error(command), 0);
	g_exec_pid = fork();
	if (g_exec_pid == -1)
		return (return_parse_error(command), 0);
	if (g_exec_pid == 0)
	{
		g_exec_pid = -2;
		free_command(m_shell->command);
		ft_free(command, NULL, m_shell->m_envp,
			heredocker(m_shell, file_name, delimiter));
	}
	waitpid(g_exec_pid, &verif, 0);
	if (verif == -1)
		return (return_parse_error(command), 0);
	command->heredoc = file_name;
	return (1);
}
