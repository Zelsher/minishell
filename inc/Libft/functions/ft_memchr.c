/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 00:00:39 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/11 00:00:39 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *ptr, int ch, size_t count)
{
	size_t	i;
	char	c;

	i = 0;
	c = (char)ch;
	while (count > i)
	{
		if (((char *)ptr)[i] == c)
			return ((void *)ptr + i);
		i++;
	}
	return (NULL);
}
