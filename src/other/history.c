/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/26 20:37:15 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_history(void)
{
	HIST_ENTRY	**history;
	int			i;

	i = 0;
	history = history_list();
	while (history[i])
	{
		printf("%d : %s\n", i, history[i]->line);
		i++;
	}
}

int	is_last_cmd(const char *new_command)
{
	HIST_ENTRY	**history;
	int			i;

	i = 0;
	history = history_list();
	while (history && history[i])
		i++;
	if (i >= 1)
	{
		if (!ft_strcmp(new_command, history[i - 1]->line))
			return (1);
	}
	return (0);
}
