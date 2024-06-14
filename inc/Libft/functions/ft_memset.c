/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:17:50 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/07 19:17:50 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *ptr, int n, size_t count)
{
	unsigned char		*charptr;

	charptr = (unsigned char *)ptr;
	while (count > 0)
	{
		*charptr = n;
		charptr++;
		count--;
	}
	return (ptr);
}
