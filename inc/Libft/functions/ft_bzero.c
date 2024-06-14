/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 01:31:09 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/08 01:31:09 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_bzero(void *ptr, size_t n)
{
	unsigned char	*charptr;

	charptr = (unsigned char *)ptr;
	while (n > 0)
	{
		*charptr = '\0';
		charptr++;
		n--;
	}
}
