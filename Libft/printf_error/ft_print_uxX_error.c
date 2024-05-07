/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 02:48:58 by eboumaza          #+#    #+#             */
/*   Updated: 2023/09/05 02:48:58 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_u_error(unsigned int u)
{
	int	i;

	i = ft_putnbr_unsigned_int_error(u, 0);
	return (i);
}

int	ft_print_x_error(unsigned int x)
{
	char	*str;
	int		i;

	if (x == 0)
	{
		ft_print_c_error('0');
		return (1);
	}
	str = ft_int_to_hexa_error(x);
	if (str == NULL)
		return (0);
	i = ft_print_s_error(str);
	free (str);
	return (i);
}

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}

int	ft_print_maj_x_error(unsigned int X)
{
	char	*str;
	int		i;

	i = 0;
	if (X == 0)
	{
		ft_print_c_error('0');
		return (1);
	}
	str = ft_int_to_hexa_error(X);
	if (str == NULL)
		return (0);
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	i = ft_print_s_error(str);
	free(str);
	return (i);
}
