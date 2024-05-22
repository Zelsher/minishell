/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/22 01:03:14 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exec_pid;

int	main(int argc, char **argv, char **envp)
{
	char				*m_envp[1000];
	struct sigaction	sa;

	ENVP_Cpy(m_envp, envp);
	if (!INIT_Receive_Signal(&sa))
		return (ft_free(NULL, NULL, m_envp, 1), 1);
	minishell(m_envp);
	return (0);
	(void)argc;
	(void)argv;
}
