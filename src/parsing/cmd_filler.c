/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_filler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/26 20:36:05 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_var(char *new_command, char *arg, char **m_envp, t_parse *parse)
{
	char	*var;

	var = find_var_envp(m_envp, new_command + parse->i + 1, 0);
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

void	handle_quote(char *new_command, char *arg,
char **m_envp, t_parse *parse)
{
	parse->quote = new_command[parse->i];
	parse->i++;
	while (new_command[parse->i] != parse->quote && new_command[parse->i])
	{
		if (parse->quote == 34 && new_command[parse->i] == '$' && (ft_isalnum(new_command[parse->i + 1]) || new_command[parse->i + 1] == '?') 
			&& new_command[parse->i + 1] != parse->quote)
			handle_var(new_command, arg, m_envp, parse);
		else
		{
			arg[parse->j] = new_command[parse->i];
			parse->i++;
			parse->j++;
		}
	}
	parse->i++;
}

int	arger(char *new_command, char *arg, char **m_envp)
{
	t_parse	parse;

	parse_construct(&parse);
	while (new_command[parse.i] && !is_in(new_command[parse.i], "\t\v\n\r "))
	{
		if (is_quote(new_command[parse.i]))
			handle_quote(new_command, arg, m_envp, &parse);
		else if (new_command[parse.i] == '$' && (ft_isalnum(new_command[parse.i + 1]) || new_command[parse.i + 1] == '?'))
			handle_var(new_command, arg, m_envp, &parse);
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
void	update_arg(t_command *command, t_parse *parse)
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
		//printf("strlen de : %ld\n%s\n_________________________\n", strlen(command->arg[parse->j - 1]) + 1, command->arg[parse->j - 1]);
	}
}

t_command	*cmd_filler(t_mshell *m_shell, char *new_command, t_command *command, char token)
{
	t_parse	parse;

	parse_construct(&parse);
	if (token == 'h')
	{
		heredoc(m_shell, command, &parse, new_command);
		command->arg[0] = strdup(command->heredoc);
		command->cmd = command->arg[0];
		if (!command->arg[0])
			return (return_parse_error(command), command);
		parse.j += 1;
	}
	while (new_command[parse.i] && parse.j < 201)
	{
		//printf("\narg %ld\n_________________________\n\n", parse.j);
		skip_ispace(new_command, &parse);
		if (!new_command[parse.i])
			break;
		command->arg[parse.j] = arg_malloc(command, new_command + parse.i, m_shell->m_envp);
		if (command->invalid || parse.i == 201)
			return (free_command(command), NULL);
		parse.i += arger(new_command + parse.i, command->arg[parse.j], m_shell->m_envp);
		update_arg(command, &parse);
	}
	return (put_p_arg(command));
}
