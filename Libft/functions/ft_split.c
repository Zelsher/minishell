/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:23:44 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/13 14:23:44 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_free_double_tab(char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	return (NULL);
}

static char	**malloc_split(const char *str, char c, size_t i, size_t j)
{
	char	**splited;

	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
			j++;
		while (str[i] != c && str[i])
			i++;
	}
	splited = malloc(sizeof(char *) * (j + 1));
	if (splited != NULL)
		splited[j] = NULL;
	return (splited);
}

static char	**ft_spliter(char **splited, const char *str, size_t i, char c)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (str[k + i])
	{
		i += k;
		k = 0;
		while (str[k + i] == c)
			i++;
		while (str[k + i] != c && str[k + i])
			k++;
		if (str[k + i] == 0 && k == 0)
			return (splited);
		splited[j] = ft_substr(str, i, k);
		if (splited[j] == NULL)
			return (ft_free_double_tab(splited));
		j++;
	}
	return (splited);
}

char	**ft_split(const char *str, char c)
{
	char	**splited;

	splited = malloc_split(str, c, 0, 0);
	if (splited == NULL)
		return (NULL);
	splited = ft_spliter(splited, str, 0, c);
	if (splited == NULL)
		return (NULL);
	return (splited);
}
