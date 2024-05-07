/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:45:11 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/10 18:45:11 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[i] == 0)
		return ((char *)haystack);
	while (n > i + 1 || haystack[i] != '\0')
	{
		j = 0;
		while (haystack[i + j] == needle[j] && needle[j])
			j++;
		if ((haystack[i + j] == '\0' && needle[j]) || i + j > n)
			return (NULL);
		if (!needle[j])
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
