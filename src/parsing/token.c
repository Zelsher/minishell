/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:58:43 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/28 17:16:52 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	token_error(t_command *command, char *new_command)
{
	if (is_in(new_command[1], "<>|&") || new_command[0] == '&')
		ft_printf_error(
				"minishell: syntax error near unexpected token `%c'\n",
				new_command[1]);
	else
		ft_printf_error(
				"minishell: syntax error near unexpected token `new_line'\n");
	command->token = 'u';
}

void	token_identifier(char *new_command, t_command *command, int *j, int i)
{
	if (new_command[0] == '>' && new_command[1] == '>')
		command->token = 'r';
	else if (new_command[0] == '<' && new_command[1] == '<')
		command->token = 'h';
	else if (!is_in(new_command[1], "<>|&") || new_command[0] != '&')
		command->token = new_command[0];
	else 
		token_error(command, new_command);
	new_command[0] = '\0';
	i++;
	if (is_in(new_command[1], "<>|&"))
		i++;
	(*j) = i;
	return ;
}

//Cherche les tokens, ignore les token entre quote#include "../inc/minishell.h"
int	tokener(char *new_command, t_command *command, int *j, char *tokens)
{
	int	i;
	int	quote;

	quote = 0;
	i = (*j);
	while (new_command[i])
	{
		if (quote == new_command[i] && quote)
			quote = 0;
		else if ((new_command[i] == 34 || new_command[i] == 39) && !quote)
			quote = new_command[i];
		if (is_in(new_command[i], tokens) && !quote)
			return (token_identifier(new_command + i, command, j, i), 1);
		i++;
	}
	if (quote)
		command->invalid = 0;
	return (0);
}
