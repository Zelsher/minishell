/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:16:57 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/20 18:19:10 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**CPY_Heredoc(char **dest, char **src)
{
	t_parse	parse;

	parse.i = 0;
	parse.j = 0;
	while (src[parse.j])
	{
		dest[parse.j] = src[parse.j];
		src[parse.j] = NULL;
		parse.j++;
	}
	dest[parse.j] = NULL;
	dest[parse.j + 1] = NULL;
	free(src);
	//envp_print(dest);
	return (dest);
}


char	*HEREDOC_Liner(char *reader, char **m_envp)
{
	char	*heredoc_line;
	
	if (!reader)
		return (NULL);
	heredoc_line = MALLOC_Heredoc_Line(reader, m_envp);
	if (heredoc_line)
		CREATE_Heredoc_Line(reader, heredoc_line, m_envp);
	free(reader);
	return (heredoc_line);
}

char	**HEREDOCKER(char *delimiter, char **m_envp, char **inputs, char *reader)
{
	t_parse	parse;
	char	**temp;

	parse.i = 1;
	while (parse.i == 1 || inputs[parse.i - 1])
	{
		reader = readline(">");
		if (!reader || ft_find_str_in_str(reader, delimiter))
		{
			if (!reader)
				ft_printf_error("minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", parse.i + 1, delimiter);
			else 
				*ft_find_str_in_str(reader, delimiter) = '\0';
			inputs[parse.i] = HEREDOC_Liner(reader, m_envp);
			break;
		}
		inputs[parse.i] = HEREDOC_Liner(reader, m_envp);
		parse.i++;
		inputs[parse.i] = NULL;
		temp = malloc(sizeof(char *) * (parse.i + 2));
		if (!temp)
			return (ft_free_double_tab(inputs), NULL);
		inputs = CPY_Heredoc(temp, inputs);
	}
	return (inputs);
}

void	HEREDOC(t_command *command, char **m_envp, int *wstatus)
{
	char	**inputs;
	t_command	*temp;

	inputs = malloc(sizeof(char *) * 3);
	if (!inputs)
		return;//??
	inputs[0] = command->left->cmd;
	if (!command->right->token)
		temp = command->right;
	else
		temp = command->right->left;
	temp->heredoc = HEREDOCKER(temp->cmd, m_envp, inputs, NULL);
	//envp_print(temp->heredoc);
	if (!temp->heredoc)
		return;
	(void)wstatus;
	if (ft_builtins(command, wstatus, m_envp) == 1)
		ft_free(command, NULL, m_envp, (*wstatus));
	execve(pathfinder(command->left, m_envp, 0), temp->heredoc, m_envp);
	exit(0);
	//wstatus = pathfinder(command, m_envp), temp->heredoc, m_envp
	//command->left->arg = command->right->heredoc
	//ft_exec(command->left, m_envp, wstatus);
	//ta partie qui utilise command->right->arg
}
