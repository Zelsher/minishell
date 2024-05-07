/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/04/19 00:11:10 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	TOKEN_Identifier(char *new_command, t_command *command, int *j, int i)
{
	if (new_command[0] == '>' && new_command[1] == '>')
		command->token = 'r';
	else if (new_command[0] == '<' && new_command[1] == '<')
		command->token = 'h';
	else if (new_command[0] == '&' && new_command[1] == '&')
		command->token = 'e';
	else if (new_command[0] == '|' && new_command[1] == '|')
		command->token = 'p';
	else if (is_in(new_command[1], "<>|&"))
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
int	TOKENER(char *new_command, t_command *command, int *j, char *tokens)
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
			return (TOKEN_Identifier(new_command + i, command, j, i), 1);
		i++;
	}
	if (quote)
		command->invalid = 0;
	return (0);
}

int	REDIRECT_Init(t_command *command)
{
	t_command	*temp;
	int			i;
	
	i = 1;
	while (command->left->arg[i])
		i++;
	temp = command->right;
	while (temp && temp->token == command->token)
	{
		command->left->arg[i] = ft_strdup(temp->left->cmd);
		if (!command->left->arg[i])
			return (0);
		temp = temp->right;
		i++;
		if (temp && temp->cmd)
		{
			command->left->arg[i] = ft_strdup(temp->cmd);
			if (!command->left->arg[i])
				return (0);
			i++;
		}
	}
	command->left->arg[i] = NULL;
	return(1);
}

//Parcours la commande, si un token est trouver, la fonction est rappeler pour la string avant le token, et apres.
t_command	*RECURSIVE_Parse(char *new_command, char **m_envp, int i)
{
	t_command	*command;

	command = CMD_Construct(new_command);
	if (!command)
		return (NULL);
	if (TOKENER(new_command, command, &i, "|&"))
	{
		command->left = RECURSIVE_Parse(new_command, m_envp, 0);
		command->right = RECURSIVE_Parse(new_command + i, m_envp, 0);
		if (!command->left || !command->right)
			return (FREE_Command(command), NULL);
	}
	if (TOKENER(new_command, command, &i, "<>"))
	{
		command->left = RECURSIVE_Parse(new_command, m_envp, 0);
		command->right = RECURSIVE_Parse(new_command + i, m_envp, 0);
		if (!command->left || !command->right)
			return (FREE_Command(command), NULL);
		if ((command->token == '>' || command->token == '<' || command->token == 'r') && !REDIRECT_Init(command))
			return (FREE_Command(command), NULL);
	}
	if (!command->token)
		command = CMD_Filler(new_command, command, m_envp);
	return (command);
}

t_command	*CMD_Parse(char *new_command, char **m_envp, int *wstatus)
{
	t_command	*command;

	command = RECURSIVE_Parse(new_command, m_envp, 0);
	if (!command)
		ft_free(NULL, new_command, m_envp, 1);
	// ft_print_command_tree(command, "tree", 1);
	if (!CMD_Verifier(command, wstatus))
	{
		if (!UPDATE_Wstatus(m_envp, wstatus, 0))
			return (ft_free(command, new_command, m_envp, 1), NULL);
		return (FREE_Command(command), NULL);
	}
	return (command);
}
