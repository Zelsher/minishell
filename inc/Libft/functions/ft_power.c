/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 18:55:13 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/07 18:55:13 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_power(int number, int power)
{
	int	result;

	if (number == 0 && power == 0)
		return (1);
	result = number;
	while (power > 1)
	{
		result *= number;
		power--;
	}
	return (result);
}
