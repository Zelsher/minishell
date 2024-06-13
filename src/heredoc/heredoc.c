/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:16:57 by eboumaza          #+#    #+#             */
/*   Updated: 2024/06/13 20:03:47 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_eof_heredoc(int line, char *delimiter)
{
	ft_printf_error("minishell: warning: here-document at line");
	ft_printf_error(" %d delimited by end-of-file (wanted `%s')\n",
		line, delimiter);
}

char	*heredoc_liner(char *reader, char **m_envp, int fd)
{
	char	*heredoc_line;

	if (!reader)
		return (NULL);
	heredoc_line = malloc_heredoc_line(reader, m_envp);
	if (heredoc_line)
	{
		create_heredoc_line(reader, heredoc_line, m_envp);
		ft_putstr_fd(heredoc_line, fd);
		free(heredoc_line);
	}
	free(reader);
	return (NULL);
}

int	heredocker(t_mshell *m_shell, char *file_name, char *delimiter, int line)
{
	char	*reader;
	int		fd;

	init_signal(2);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (free(file_name), -1);
	while (1)
	{
		reader = readline(">");
		if (!reader || !ft_strcmp(delimiter, reader) || g_exec_pid == -1)
		{
			if (!reader)
				print_eof_heredoc(m_shell->line, delimiter);
			else
				free(reader);
			m_shell += line;
			break ;
		}
		heredoc_liner(reader, m_shell->m_envp, fd);
		line++;
	}
	close(fd);
	return (free(file_name), 1);
}

void	skip_delimiter(char *new_command, t_parse *parse)
{
	while (is_in(new_command[parse->i], "\t\v\n\r ") && new_command[parse->i])
		parse->i++;
	while (!is_in(new_command[parse->i], "\t\v\n\r ") && new_command[parse->i])
		parse->i++;
}

int	heredoc(t_mshell *m_shell, t_command *command,
	t_parse *parse, char *new_command)
{
	static size_t	count;
	int				verif;
	char			*file_name;

	file_name = generate_file(&count);
	if (!file_name)
		return (return_parse_error(command), 0);
	g_exec_pid = fork();
	if (g_exec_pid == -1)
		return (return_parse_error(command), 0);
	if (g_exec_pid == 0)
	{
		free_command(m_shell->command);
		ft_free(command, NULL, m_shell->m_envp,
			heredocker(m_shell, file_name,
				find_delimiter(new_command, parse), 0));
	}
	wait_child(g_exec_pid, &verif);
	if (verif != -1)
		command->heredoc = file_name;
	if (g_exec_pid <= -1)
		return (printf("\n"), return_parse_error(command), 0);
	command->arg[0] = ft_strdup(command->heredoc);
	g_exec_pid = 0;
	return (skip_delimiter(new_command, parse), 1);
}
