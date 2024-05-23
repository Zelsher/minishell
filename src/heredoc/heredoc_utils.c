/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:18:59 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/23 02:32:47 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	create_file_name(int nb, char *file_name, int temp, int count)
{
	int	i;

	file_name[(ft_nbrlen(nb) + 10)] = '\0';
	ft_strcpy(file_name, ".temp_file");
	i = 0;
	while (nb != 0)
	{
		temp = nb;
		count = 1;
		while (temp >= 10)
		{
			temp /= 10;
			count *= 10;
		}
		file_name[10 + i] = temp + '0';
		nb -= temp * count;
		while (count > nb * 10 && count != 1)
		{
			i++;
			count /= 10;
			file_name[10 + i] = '0';
		}
		i++;
	}
	//printf("heredoc_file : %s\n", file_name);
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
