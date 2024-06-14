/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_str_in_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 18:55:13 by eboumaza          #+#    #+#             */
/*   Updated: 2024/05/20 21:03:58 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_find_str_in_str(char *str, char *searched)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	j = 0;
	if (!str || !searched || ft_strlen(str) < ft_strlen(searched))
		return (NULL);
	while (str[i])
	{
		j = 0;
		while (str[i + j] && searched[j] && searched[j] == str[i + j])
		{
			if (!j)
				temp = str + i;
			j++;
		}
		if (!searched[j])
			return (temp);
		else
			temp = NULL;
		i++;
	}
	return (NULL);
}
