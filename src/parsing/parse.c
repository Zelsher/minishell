/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/26 21:11:58 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	token_identifier(char *new_command, t_command *command, int *j, int i)
{
	if (new_command[0] == '>' && new_command[1] == '>')
		command->token = 'r';
	else if (new_command[0] == '<' && new_command[1] == '<')
		command->token = 'h';
	else if (new_command[0] == '&' && new_command[1] == '&')
		command->token = 'e';
	else if (new_command[0] == '|' && new_command[1] == '|')
		command->token = 'p';
	else if (is_in(new_command[1], "<>|&") || 0) //mettre pr les new_line (syntax error near unexpected token `newline')
	{
		command->token = 'u';
		command->invalid_token = *new_command + 1;
	}
	else
		command->token = new_command[0];
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

int	redirect_init(t_command *command)
{
	t_command	*temp;
	int			i;

	i = 0;
	temp = command->right;
	while (command->left->arg[i])
		i++;
	if (i > 199)
		return (0);
	if (temp->token)
		temp = temp->left;
	command->left->arg[i] = strdup(temp->arg[0]);
	if (!command->left->arg[i])
		return (0);
	command->left->arg[i + 1] = NULL;
	return (1);
}

t_command	*recurs_parse(t_mshell *m_shell, char *new_command,
	int i, char token)
{
	t_command	*command;

	command = cmd_construct(m_shell, token);
	if (!command)
		return (NULL);
	if (tokener(new_command, command, &i, "|&"))
	{
		command->left = recurs_parse(m_shell, new_command, 0, command->token);
		command->right = recurs_parse(m_shell, new_command + i, 0, command->token);
		if (!command->left || !command->right)
			return (free_command(command), NULL);
	}
	if (tokener(new_command, command, &i, "<>"))
	{
		command->left = recurs_parse(m_shell, new_command, 0, '0');
		command->right = recurs_parse(m_shell, new_command + i, 0, command->token);
		if (!command->left || !command->right)
			return (free_command(command), NULL);
	}
	if (!command->token)
		command = cmd_filler(m_shell, new_command, command, token);
	return (command);
}

t_command	*cmd_parse(t_mshell *m_shell, char *new_command, char **m_envp, int *wstatus)
{
	t_command	*command;

	command = recurs_parse(m_shell, new_command, 0, 't');
	free(new_command);
	if (!command)
		ft_free(command, NULL, m_envp, 1);
	if (!cmd_verifier(command, wstatus))
	{
		if (!update_wstatus(m_envp, wstatus, 0))
			return (ft_free(command, NULL, m_envp, 1), NULL);
		return (free_command(command), NULL);
	}
	return (command);
}
