/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 00:43:58 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/30 00:43:58 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr_error(int nbr, int i)
{
	char		c;

	if (nbr < 0)
	{
		c = 45;
		write (1, &c, 1);
		nbr = -nbr;
		i++;
	}
	if (nbr >= 10)
	{
		i = ft_putnbr_error(nbr / 10, i);
		i = ft_putnbr_error(nbr % 10, i);
	}
	else
	{
		c = nbr + '0';
		write(2, &c, 1);
		i++;
	}
	return (i);
}
