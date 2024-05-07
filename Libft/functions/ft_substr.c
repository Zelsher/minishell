/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:30:55 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/12 20:30:55 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	i;

	if (start >= ft_strlen(str))
		len = 0;
	else if (len > ft_strlen(str + start))
		len = ft_strlen(str + start);
	newstr = malloc(sizeof(char) * (len + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	while (start + i < ft_strlen(str) && i < len)
	{
		newstr[i] = str[start + i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
