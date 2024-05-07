/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 00:27:58 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/13 00:27:58 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	len;
	char	*joiner;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	joiner = malloc(sizeof(char) * len);
	if (joiner == NULL)
		return (NULL);
	while (s1[i])
	{
		joiner[i] = s1[i];
		i++;
	}
	len = i;
	i = 0;
	while (s2[i])
	{
		joiner[i + len] = s2[i];
		i++;
	}
	joiner[i + len] = '\0';
	return (joiner);
}
