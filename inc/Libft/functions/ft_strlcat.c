/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:55:14 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/10 14:55:14 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	b;

	i = 0;
	b = 0;
	while (dst[i])
		i++;
	while (src[b] && (i + 1) < (size))
	{
		dst[i] = src[b];
		i++;
		b++;
	}
	dst[i] = 0;
	if (i > size)
		return (size + ft_strlen(src));
	while (src[b])
	{
		i++;
		b++;
	}
	return (i);
}
