/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 00:45:43 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/11 00:45:43 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;

	if (size != 0 && n > ((size_t) -1 / size))
		return (NULL);
	ptr = (void *) malloc(size * n);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, size * n);
	return (ptr);
}
