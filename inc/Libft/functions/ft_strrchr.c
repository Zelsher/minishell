/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:32:16 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/10 15:32:16 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t		i;
	char		*find;
	char		ch;

	i = 0;
	ch = (char)c;
	find = NULL;
	while (str[i])
	{
		if (str[i] == ch)
			find = (char *)&str[i];
		i++;
	}
	if (ch == 0)
		return ((char *)str + i);
	return (find);
}
