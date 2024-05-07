/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr_max_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:17:50 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/07 19:17:50 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../libft.h"

long long int	ft_nbr_max_pos(long long int nbr)
{
	long long int   max_pos;

	max_pos = 1;
	if (nbr < 0)
		nbr *= -1;
	while (nbr >= 10)
	{
		max_pos *= 10;
		nbr /= 10;
	}
	return (max_pos);
}