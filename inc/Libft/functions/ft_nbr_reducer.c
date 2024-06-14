/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr_reducer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:56:59 by eboumaza          #+#    #+#             */
/*   Updated: 2023/12/25 19:19:27 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

long long int	ft_nbr_reducer(long long int nbr, int digit)
{
	long long int	count;
	long long int	temp;

	if (digit <= 0)
		return (0);
	if (nbr < 0)
		nbr *= -1;
	if (ft_power(10, digit) < 0)
		return (nbr);
	while (nbr > ft_power(10, digit))
	{
		count = 1;
		temp = nbr;
		while (temp >= 10)
		{
			temp /= 10;
			count *= 10;
		}
		nbr -= temp * count;
	}
	return (nbr);
}
