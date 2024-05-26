/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/26 16:56:03 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	HANDLE_Var_Malloc(char *new_command, char **m_envp, t_parse *parse)
{
	char	*var;

	var = FIND_Var_Envp(m_envp, new_command + parse->i + 1, 0);
	if (var)
		parse->j += ft_strlen(var);
	if (new_command[parse->i + 1] == '?')
	{
		parse->i += 2;
		return;
	}
	while (new_command[parse->i] && !is_quote(new_command[parse->i])
		&& !is_in(new_command[parse->i], "\t\v\n\r "))
		parse->i++;
}

void	HANDLE_Quote_Malloc(char *new_command, char **m_envp, t_parse *parse)
{
	parse->quote = new_command[parse->i];
	parse->i++;
	while (new_command[parse->i] && new_command[parse->i] != parse->quote)
	{
		if (parse->quote == 34 && new_command[parse->i] == '$' && (ft_isalnum(new_command[parse->i + 1]) || new_command[parse->i + 1] == '?') 
			&& new_command[parse->i + 1] != parse->quote)
			HANDLE_Var_Malloc(new_command, m_envp, parse);
		else
		{
			parse->i++;
			parse->j++;
		}
	}
	if (new_command[parse->i])
		parse->i++;
}

char	*ARG_Malloc(t_command *command, char *new_command, char **m_envp)
{
	t_parse		parse;
	char		*arg;

	PARSE_Construct(&parse);
	while (new_command[parse.i] && !is_in(new_command[parse.i], "\t\v\n\r "))
	{
		if (is_quote(new_command[parse.i]))
			HANDLE_Quote_Malloc(new_command, m_envp, &parse);
		else if (new_command[parse.i] == '$' && (ft_isalnum(new_command[parse.i + 1]) || new_command[parse.i + 1] == '?'))
			HANDLE_Var_Malloc(new_command, m_envp, &parse);
		else
		{
			parse.i++;
			parse.j++;
		}
	}
	if (!parse.j)
		return (NULL);
	arg = malloc(sizeof(char) * (parse.j + 1));;
	if (!arg)
		command->invalid = 999;
	//printf("malloc de %ld\n", parse.j + 1);
	return (arg);
}
