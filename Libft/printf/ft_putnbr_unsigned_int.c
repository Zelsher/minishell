/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned_int.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:19:49 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/30 15:19:49 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr_unsigned_int(unsigned int nbr, int i)
{
	char		c;

	if (nbr >= 10)
	{
		i = ft_putnbr(nbr / 10, i);
		i = ft_putnbr(nbr % 10, i);
	}
	if (nbr < 10)
	{
		c = nbr + '0';
		write(1, &c, 1);
		i++;
	}
	return (i);
}
