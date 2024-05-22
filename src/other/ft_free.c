/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/22 23:05:47 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_envp(char **m_envp)
{
	int	i;

	i = 0;
	if (!m_envp)
		return ;
	while (m_envp[i])
	{
		free(m_envp[i]);
		i++;
	}
}

void	FREE_Command(t_command *command)
{
	int	i;

	i = 0;
	if (!command)
		return ;
	if (command->left)
		FREE_Command(command->left);
	if (command->right)
		FREE_Command(command->right);
	while (command->arg[i])
	{
		free(command->arg[i]);
		command->arg[i] = NULL;
		i++;
	}
	if (command->heredoc)
	{
		unlink(command->heredoc);
		free(command->heredoc);
	}
	free(command);
	return ;
}

void	ft_free(t_command *command, char *new_command, char **m_envp, int m_exit)
{
	FREE_Command(command);
	ft_free_envp(m_envp);
	if (new_command)
	{
		free(new_command); 
		new_command = NULL;
	}
	if (m_exit)
		exit(m_exit);
}

int	CMD_Verifier(t_command *command, int *wstatus)
{
	int	verif;

	verif = 1;
	if (command->invalid)
		(*wstatus) = command->invalid;
	if (command->token == 'u')
		return (ft_printf_error("minishell: syntax error near unexpected token `%d'\n", command->invalid_token), 0);
	else if ( (!command->token && !command->cmd))
		return (0);
	if (command->left)
		verif = CMD_Verifier(command->left, wstatus);
	if (verif == 0)
		return (verif);
	if (command->right)
		verif = CMD_Verifier(command->right, wstatus);
	if (verif == 0)
		return (verif);
	return (verif);
}

void return_parse_error(t_command *command)
{
	command->invalid = 1;
	return ;
}

void	ft_print_command_tree(t_command *command, char *branch, int i)
{
	int	j;

	if (i == 1)
	{
		if (command->invalid)
			printf("\n\nUnvalid\n");
		printf("\x1B[1;31m%s Node %d :\ntoken :%c\ncmd :%s\n\x1B[0m", branch, i, command->token, command->cmd);
		j = 0;
		while (command->arg[j])
		{
			if (j == 0)
				printf("\x1B[1;31marg_cmd :\x1B[0m");
			if (command->p_opt == command->arg[j])
				printf("\x1B[1;31m\nopt :\x1B[0m");
			if (command->p_file == command->arg[j])
				printf("\x1B[1;31m\nfile :\x1B[0m");
			printf("\x1B[1;31m[%s] \x1B[0m", command->arg[j]);
			j++;
		}
		printf("\n\n");
	}
	if (i == 2)
	{
		if (command->invalid)
			printf("Unvalid\n");
		printf("\n\n\x1B[1;32m%s Node %d :\ntoken :%c\ncmd :%s\n\x1B[0m", branch, i, command->token, command->cmd);
		j = 0;
		while (command->arg[j])
		{
			if (j == 0)
				printf("\x1B[1;32marg_cmd :\x1B[0m");
			if (command->p_opt == command->arg[j])
				printf("\x1B[1;32m\nopt :\x1B[0m");
			if (command->p_file == command->arg[j])
				printf("\x1B[1;32m\nfile :\x1B[0m");
			printf("\x1B[1;32m[%s] \x1B[0m", command->arg[j]);
			j++;
		}
		printf("\n\n");
	}
	if (i == 3)
	{
		if (command->invalid)
			printf("Unvalid\n");
		printf("\n\n\x1B[1;33m%s Node %d :\ntoken :%c\ncmd :%s\n\x1B[0m", branch, i, command->token, command->cmd);
		j = 0;
		while (command->arg[j])
		{
			if (j == 0)
				printf("\x1B[1;33marg_cmd :\x1B[0m");
			if (command->p_opt == command->arg[j])
				printf("\x1B[1;33m\nopt :\x1B[0m");
			if (command->p_file == command->arg[j])
				printf("\x1B[1;33m\nfile :\x1B[0m");
			printf("\x1B[1;33m[%s] \x1B[0m", command->arg[j]);
			j++;
		}
		printf("\n\n");
	}
	if (i == 4)
	{
		if (command->invalid)
			printf("Unvalid\n");
		printf("\n\n\x1B[1;34m%s Node %d :\ntoken :%c\ncmd :%s\n\x1B[0m", branch, i, command->token, command->cmd);
		j = 0;
		while (command->arg[j])
		{
			if (j == 0)
				printf("\x1B[1;34marg_cmd :\x1B[0m");
			if (command->p_opt == command->arg[j])
				printf("\x1B[1;34m\nopt :\x1B[0m");
			if (command->p_file == command->arg[j])
				printf("\x1B[1;34m\nfile :\x1B[0m");
			printf("\x1B[1;34m[%s] \x1B[0m", command->arg[j]);
			j++;
		}
		printf("\n\n");
	}
	if (i == 5)
	{
		if (command->invalid)
			printf("Unvalid\n");
		printf("\n\n\x1B[1;35m%s Node %d :\ntoken :%c\ncmd :%s\n\x1B[0m", branch, i, command->token, command->cmd);
		j = 0;
		while (command->arg[j])
		{
			if (j == 0)
				printf("\x1B[1;35marg_cmd :\x1B[0m");
			if (command->p_opt == command->arg[j])
				printf("\x1B[1;35m\nopt :\x1B[0m");
			if (command->p_file == command->arg[j])
				printf("\x1B[1;35m\nfile :\x1B[0m");
			printf("\x1B[1;35m[%s] \x1B[0m", command->arg[j]);
			j++;
		}
		printf("\n\n");
	}
	if (command->left)
		ft_print_command_tree(command->left, "left", i + 1);
	if (command->right)
		ft_print_command_tree(command->right, "right", i + 1);
}

void	print_cmd(t_command *command)
{
	static int	show;

	if (!command)
		return ;
	if (command->arg[0] && !ft_strcmp(command->arg[0], "unshow"))
		show = 0;
	if (show)
		ft_print_command_tree(command, "tree", 1);
	if (command->arg[0] && !ft_strcmp(command->arg[0], "show"))
		show = 1;
}
