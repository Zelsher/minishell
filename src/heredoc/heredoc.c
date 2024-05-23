/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:16:57 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/23 02:29:34 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_delimiter(char *new_command, t_parse *parse)
{
	char	*p_delimiter;

	parse->i = 0;
	while (is_in(new_command[parse->i], "\t\v\n\r ") && new_command[parse->i])
		parse->i += 1;
	p_delimiter = new_command + parse->i;
	while (!is_in(new_command[parse->i], "\t\v\n\r ") && new_command[parse->i])
		parse->i += 1;
	if (new_command[parse->i])
	{
		parse->i += 1;
		new_command[parse->i - 1] = '\0';
	}
	return (p_delimiter);
}

char	*HEREDOC_Liner(char *reader, char **m_envp, int fd)
{
	char	*heredoc_line;
	
	if (!reader)
		return(NULL);
	heredoc_line = MALLOC_Heredoc_Line(reader, m_envp);
	if (heredoc_line)
	{
		CREATE_Heredoc_Line(reader, heredoc_line, m_envp);
		ft_putstr_fd(heredoc_line, fd);
		free(heredoc_line);
		//free(reader);
	}
	free(reader);
	return (NULL);
}

int	HEREDOCKER(char *file_name, char *delimiter, char **m_envp)
{
	char 	*reader;
	int		i;
	int 	fd;

	i = 0;
	g_exec_pid = -2;
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1)
		return (-1);
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
		HEREDOC_Liner(reader, m_envp, fd);
	}
	close(fd);
	return (1);
}

int	HEREDOC(t_mshell *m_shell, t_command *command, t_parse *parse, char *new_command)
{
	static int	count;
	char		*delimiter;
	int			verif;
	
	delimiter = find_delimiter(new_command, parse);
	command->heredoc = malloc(sizeof(char) * ft_nbrlen(count) + 11);
	if (!command->heredoc)
		return (return_parse_error(command), 0);
	create_file_name(count, command->heredoc, 0, 0);
	count++;
	g_exec_pid = fork();
	if (g_exec_pid == -1)
		return (return_parse_error(command), 0);
	if (g_exec_pid == 0)
	{
		FREE_Command(m_shell->command);
		ft_free(command, NULL, m_shell->m_envp,
			HEREDOCKER(command->heredoc, delimiter, m_shell->m_envp));
	}
	waitpid(g_exec_pid, &verif, 0);
	g_exec_pid = 0;
	if (verif == -1)
		return (free(command->heredoc), return_parse_error(command), 0);
	return (1);
}
