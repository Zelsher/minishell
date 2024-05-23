/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:18:59 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/23 23:49:18 by eboumaza         ###   ########.fr       */
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

void	Handle_Var_Malloc_Heredoc(char *reader, char **m_envp, t_parse *parse)
{
	if (FIND_Var_Envp(m_envp, reader + parse->i + 1, 0))
		parse->j += ft_strlen(
				FIND_Var_Envp(m_envp, reader + parse->i + 1, 0));
	while (reader[parse->i] && !is_quote(reader[parse->i])
		&& !is_in(reader[parse->i], "\t\v\n\r "))
		parse->i++;
}

char	*MALLOC_Heredoc_Line(char *reader, char **m_envp)
{
	t_parse	    parse;
	char		*here_doc_line;

	PARSE_Construct(&parse);
	while (reader[parse.i])
	{
		if (reader[parse.i] == '$' && (ft_isalnum(reader[parse.i + 1]) || reader[parse.i + 1] == '?'))//new_command[parse->i] == '$' && (ft_isalnum(new_command[parse.i + 1]
			Handle_Var_Malloc_Heredoc(reader, m_envp, &parse);
		else
		{
			parse.i++;
			parse.j++;
		}
	}
	here_doc_line = malloc(sizeof(char) * parse.j + 2);
	return (here_doc_line);
}

void	HANDLE_Var_Line_Heredoc(char *reader, char *here_doc_line, char **m_envp, t_parse *parse)
{
	if (FIND_Var_Envp(m_envp, reader + parse->i + 1, 0))
	{
		ft_strcpy(here_doc_line + parse->j,
			FIND_Var_Envp(m_envp, reader + parse->i + 1, 0));
		parse->j += ft_strlen(
				FIND_Var_Envp(m_envp, reader + parse->i + 1, 0));
	}
	while (reader[parse->i] && !is_quote(reader[parse->i])
		&& !is_in(reader[parse->i], "\t\v\n\r "))
		parse->i++;
}

int	CREATE_Heredoc_Line(char *reader, char *here_doc_line, char **m_envp)
{
	t_parse	parse;

	PARSE_Construct(&parse);
	while (reader[parse.i])
	{
		if (reader[parse.i] == '$' && (ft_isalnum(reader[parse.i + 1]) || reader[parse.i + 1] == '?'))
			HANDLE_Var_Line_Heredoc(reader, here_doc_line, m_envp, &parse);
		else
		{
			here_doc_line[parse.j] = reader[parse.i];
			parse.j++;
			parse.i++;
		}
	}
	here_doc_line[parse.j] = '\n';
	here_doc_line[parse.j + 1] = '\0';
	//printf("str_len de %s : %ld\n", here_doc_line, ft_strlen(here_doc_line) + 1);
	return (parse.i);
}
