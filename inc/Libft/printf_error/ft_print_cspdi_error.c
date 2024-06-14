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

int	ft_print_c_error(int c)
{
	write(2, &c, 1);
	return (1);
}

int	ft_print_s_error(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		i += 6;
		write (2, "(null)", 6);
		return (i);
	}
	while (s[i])
	{
		write (2, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_print_p_error(unsigned long int p)
{
	int		i;
	char	*str;

	if (p == 0)
	{
		write (2, "(nil)", 5);
		return (5);
	}
	write (2, "0x", 2);
	str = ft_putptr_error(p);
	if (str == NULL)
		return (0);
	i = ft_print_s_error(str) + 2;
	free (str);
	return (i);
}

int	ft_print_d_error(int d)
{
	int	i;

	if (d == -2147483648)
	{
		write (2, "-2147483648", 11);
		return (11);
	}
	i = ft_putnbr_error(d, 0);
	return (i);
}

int	ft_print_i_error(int i)
{
	int				j;

	if (i > 0)
		j = ft_putnbr_unsigned_int_error((unsigned int)i, 0);
	else
		j = ft_print_d_error(i);
	return (j);
}
