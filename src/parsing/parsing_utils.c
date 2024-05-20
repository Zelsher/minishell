/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/20 18:19:22 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_command	*CMD_Construct(char *new_command)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->invalid = 0;
	command->type = 0;
	command->token = 0;
	command->cmd = NULL;
	command->heredoc = NULL;
	command->arg[0] = NULL;
	command->arg[1] = NULL;
	command->quote[0] = 0;
	command->p_opt = NULL;
	command->p_file = NULL;
	command->p_new_command = new_command;
	command->left = NULL;
	command->right = NULL;
	return (command);
}

void	PARSE_Construct(t_parse *parse)
{
	parse->i = 0;
	parse->j = 0;
	parse->quote = 0;
}

t_command	*PUT_P_Arg(t_command *command)
{
	int	i;

	i = 0;
	command->cmd = command->arg[0];
	while (command->arg[i] && i < 200)
	{
		if (!command->p_opt && i == 1 && command->arg[i][0] == '-') //repere option
			command->p_opt = command->arg[i];
		else if (!command->p_file && i >= 1 && command->arg[i][0] != '-') //repere file
			command->p_file = command->arg[i];
		i++;
	}
	if (i == 200)
		command->invalid = 7;
	return (command);
}
void	skip_ispace(char *new_command, t_parse *parse)
{
	while (is_in(new_command[parse->i], "\t\v\n\r "))
		parse->i++;
}
