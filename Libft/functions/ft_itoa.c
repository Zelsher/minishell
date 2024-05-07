/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:48:43 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/09 14:48:43 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_itoa_min_int(void)
{
	char	*str;

	str = malloc(sizeof(char) * 12);
	if (!str)
		return (NULL);
	ft_strcpy(str, "-2147483648");
	return (str);
}

static char	*ft_itoastr(char *str, int n, int count)
{
	int	minus;

	minus = 0;
	if (n < 0)
	{
		str[minus] = '-';
		n *= -1;
		minus++;
	}
	str[count - 1] = '\0';
	while (count - 1 > minus)
	{
		str[count - 2] = (n % 10) + '0';
		n = n / 10;
		count--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		count;
	int		temp;

	if (n == -2147483648)
		return (ft_itoa_min_int());
	count = 2;
	temp = n;
	if (temp < 0)
	{
		temp *= -1;
		count++;
	}
	while (temp >= 10)
	{
		count += 1;
		temp /= 10;
	}
	str = malloc(sizeof(char) * count);
	if (str == NULL)
		return (NULL);
	str = ft_itoastr(str, n, count);
	return (str);
}
