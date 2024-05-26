/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:58:16 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/26 20:46:42 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	match_path_count(char *command, char **path)
{
	int		i;
	char	*path_temp;

	i = 0;
	while (path[i])
	{
		path_temp = ft_strjoin(path[i], command);
		if (!path_temp)
			return (-1);
		i++;
		if (access(path_temp, X_OK) == 0)
		{
			free(path_temp);
			return (i);
		}
		free(path_temp);
	}
	return (0);
}

char	**putlastslash(char **path)
{
	int		i;
	char	**path_temp;

	i = 0;
	while (path[i])
		i++;
	path_temp = malloc(sizeof(char *) * (i + 1));
	if (!path_temp)
		return (NULL);
	path_temp[0] = NULL;
	i = 0;
	while (path[i])
	{
		path_temp[i] = ft_strjoin(path[i], "/");
		if (path_temp[i] == NULL)
			return (NULL);
		i++;
	}
	path_temp[i] = NULL;
	return (path_temp);
}

char	*pathfinder(t_command *command, char **m_envp, int *flag)
{
	char	**path_list;
	char	**path_temp;
	char	*path;
	int		path_index;

	if (ft_strchr(command->cmd, '/'))
		return ((*flag)++, command->cmd);
	path_temp = ft_split((find_var_envp(m_envp, "PATH", 0) + 5), ':');
	if (!path_temp)
		return (NULL);
	path_list = putlastslash(path_temp);
	if (!path_list)
		return (NULL);
	path_index = match_path_count(command->cmd, path_list);
	if (path_index > 0)
	{
		path = ft_strjoin(path_list[path_index - 1], command->cmd);
		return (ft_free_double_tab(path_temp), \
				ft_free_double_tab(path_list), path);
	}
	ft_free_double_tab(path_temp);
	ft_free_double_tab(path_list);
	return (NULL);
}
