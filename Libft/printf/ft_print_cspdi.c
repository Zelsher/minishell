/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:42:43 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/29 23:42:43 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_c(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_s(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		i += 6;
		write (1, "(null)", 6);
		return (i);
	}
	while (s[i])
	{
		write (1, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_print_p(unsigned long int p)
{
	int		i;
	char	*str;

	if (p == 0)
	{
		write (1, "(nil)", 5);
		return (5);
	}
	write (1, "0x", 2);
	str = ft_putptr(p);
	if (str == NULL)
		return (0);
	i = ft_print_s(str) + 2;
	free (str);
	return (i);
}

int	ft_print_d(int d)
{
	int	i;

	if (d == -2147483648)
	{
		write (1, "-2147483648", 11);
		return (11);
	}
	i = ft_putnbr(d, 0);
	return (i);
}

int	ft_print_i(int i)
{
	int				j;

	if (i > 0)
		j = ft_putnbr_unsigned_int((unsigned int)i, 0);
	else
		j = ft_print_d(i);
	return (j);
}
