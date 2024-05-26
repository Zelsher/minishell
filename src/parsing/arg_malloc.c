/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/26 20:44:55 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_var_malloc(char *new_command, char **m_envp, t_parse *parse)
{
	char	*var;

	var = find_var_envp(m_envp, new_command + parse->i + 1, 0);
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

void	handle_quote_malloc(char *new_command, char **m_envp, t_parse *parse)
{
	parse->quote = new_command[parse->i];
	parse->i++;
	while (new_command[parse->i] && new_command[parse->i] != parse->quote)
	{
		if (parse->quote == 34 && new_command[parse->i] == '$' && (ft_isalnum(new_command[parse->i + 1]) || new_command[parse->i + 1] == '?') 
			&& new_command[parse->i + 1] != parse->quote)
			handle_var_malloc(new_command, m_envp, parse);
		else
		{
			parse->i++;
			parse->j++;
		}
	}
	if (new_command[parse->i])
		parse->i++;
}

char	*arg_malloc(t_command *command, char *new_command, char **m_envp)
{
	t_parse		parse;
	char		*arg;

	parse_construct(&parse);
	while (new_command[parse.i] && !is_in(new_command[parse.i], "\t\v\n\r "))
	{
		if (is_quote(new_command[parse.i]))
			handle_quote_malloc(new_command, m_envp, &parse);
		else if (new_command[parse.i] == '$' && (ft_isalnum(new_command[parse.i + 1]) || new_command[parse.i + 1] == '?'))
			handle_var_malloc(new_command, m_envp, &parse);
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
