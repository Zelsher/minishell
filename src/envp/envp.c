/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:00 by eboumaza          #+#    #+#             */
/*   Updated: 2024/06/09 21:54:31 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	same_var(char *m_envp_var, char *var)
{
	size_t	i;

	i = 0;
	if (!var)
		return (0);
	if (var[0] == '?')
		return (1);
	while (var[i] && ft_isalnum(var[i]))
		i++;
	if (i == 0 || (i < ft_strlen(m_envp_var) && m_envp_var[i] != '='))
		return (0);
	if (!ft_strncmp(m_envp_var, var, i))
		return (1);
	return (0);
}

int	verify_var(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (1);
		if (!ft_isalnum(var[i]))
			return (printerr(2, "export:", "not a valid identifier", 1), 0);
		i++;
	}
	return (-1);
}

int	export_envp(char **m_envp, char *cmd)
{
	int		i;
	char	*var;

	i = 0;
	var = ft_strdup(cmd);
	if (!var)
		return (1);
	if (verify_var(cmd) <= 0)
		return (free(var), 1);
	while (m_envp[i] && cmd[0] != '?')
	{
		if (same_var(m_envp[i], var))
		{
			free(m_envp[i]);
			m_envp[i] = var;
			return (0);
		}
		i++;
		if (i >= 1000)
			return (1);
	}
	m_envp[i] = var;
	m_envp[i + 1] = NULL;
	return (0);
}

void	unset_envp(char **m_envp, char *cmd)
{
	int	i;

	i = 0;
	while (m_envp[i] && cmd[0] != '?')
	{
		if (same_var(m_envp[i], cmd))
		{
			free(m_envp[i]);
			if (!m_envp[i + 1])
			{
				m_envp[i] = NULL;
				return ;
			}
			while (m_envp[i + 1])
			{
				m_envp[i] = m_envp[i + 1];
				i++;
			}
			m_envp[i - 1] = ft_strdup(m_envp[i]);
			free(m_envp[i]);
			m_envp[i] = 0;
		}
		i++;
	}
}

char	*find_var_envp(char **m_envp, char *var, int verif)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (m_envp[i] && !same_var(m_envp[i], var))
		i++;
	if (!m_envp[i])
		return (NULL);
	if (verif)
		return (m_envp[i]);
	while (m_envp[i][j] != '=')
		j++;
	return (m_envp[i] + j + 1);
}
