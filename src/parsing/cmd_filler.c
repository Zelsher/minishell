/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_filler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/21 01:05:52 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	HANDLE_Var(char *new_command, char *arg, char **m_envp, t_parse *parse)
{
	char	*var;

	//rintf("oui filler\n");
	var = FIND_Var_Envp(m_envp, new_command + parse->i + 1, 0);
	if (var)
	{
		ft_strcpy(arg + parse->j, var);
		parse->j += ft_strlen(var);
	}
	if (new_command[parse->i + 1] == '?')
	{
		parse->i += 2;
		return;
	}
	while (new_command[parse->i] && !is_quote(new_command[parse->i])
		&& !is_in(new_command[parse->i], "\t\v\n\r "))
		parse->i++;
}

void	HANDLE_Quote(char *new_command, char *arg,
char **m_envp, t_parse *parse)
{
	parse->quote = new_command[parse->i];
	parse->i++;
	while (new_command[parse->i] != parse->quote && new_command[parse->i])
	{
		if (parse->quote == 34 && new_command[parse->i] == '$' && (ft_isalnum(new_command[parse->i + 1]) || new_command[parse->i + 1] == '?') 
			&& new_command[parse->i + 1] != parse->quote)
			HANDLE_Var(new_command, arg, m_envp, parse);
		else
		{
			arg[parse->j] = new_command[parse->i];
			parse->i++;
			parse->j++;
		}
	}
	parse->i++;
}

int	ARGER(char *new_command, char *arg, char **m_envp)
{
	t_parse	parse;

	PARSE_Construct(&parse);
	while (new_command[parse.i] && !is_in(new_command[parse.i], "\t\v\n\r "))
	{
		if (is_quote(new_command[parse.i]))
			HANDLE_Quote(new_command, arg, m_envp, &parse);
		else if (new_command[parse.i] == '$' && (ft_isalnum(new_command[parse.i + 1]) || new_command[parse.i + 1] == '?'))
			HANDLE_Var(new_command, arg, m_envp, &parse);
		else
		{
			arg[parse.j] = new_command[parse.i];
			parse.j++;
			parse.i++;
		}
	}
	if (arg)
		arg[parse.j] = '\0';
	return (parse.i);
}
void	UPDATE_Arg(t_command *command, t_parse *parse)
{
	if (!command->arg)
	{
		if (command->arg[parse->j])
			free(command->arg[parse->j]);
		command->arg[parse->j] = NULL;
	}
	else
	{
		parse->j++;
		command->arg[parse->j] = NULL;
		//printf("strlen de : %ld\n%s\n_________________________\n", strlen(command->arg[parse.j - 1]) + 1, command->arg[parse.j - 1]);
	}
}

t_command	*CMD_Filler(char *new_command, t_command *command, char **m_envp, char token)
{
	t_parse	parse;

	PARSE_Construct(&parse);
	if (token == 'h')
		HEREDOC(command, m_envp, &parse, new_command);
	while (new_command[parse.i] && parse.j < 201)
	{
		//printf("\narg %ld\n_________________________\n\n", parse.j);
		skip_ispace(new_command, &parse);
		if (!new_command[parse.i])
			break;
		command->arg[parse.j] = ARG_Malloc(command, new_command + parse.i, m_envp);
		if (command->invalid || parse.i == 201)
			return (FREE_Command(command), NULL);
		parse.i += ARGER(new_command + parse.i, command->arg[parse.j], m_envp);
		UPDATE_Arg(command, &parse);
	}
	return (PUT_P_Arg(command));
}
