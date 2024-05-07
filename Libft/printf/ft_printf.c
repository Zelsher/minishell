/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:06:05 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/29 18:06:05 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*cspdiuxX%*/

#include "../libft.h"

int	ft_print_format(va_list ap, char c)
{
	size_t	printed_char;

	if (c == 'c')
		printed_char = ft_print_c(va_arg(ap, int));
	else if (c == 's')
		printed_char = ft_print_s(va_arg(ap, char *));
	else if (c == 'p')
		printed_char = ft_print_p(va_arg(ap, unsigned long int));
	else if (c == 'd')
		printed_char = ft_print_d(va_arg(ap, int));
	else if (c == 'i')
		printed_char = ft_print_i(va_arg(ap, int));
	else if (c == 'u')
		printed_char = ft_print_u(va_arg(ap, unsigned int));
	else if (c == 'x')
		printed_char = ft_print_x(va_arg(ap, unsigned int));
	else if (c == 'X')
		printed_char = ft_print_maj_x(va_arg(ap, unsigned int));
	return (printed_char);
}

const char	*ft_printfer(const char *str)
{
	int		j;

	j = 0;
	while (str[j])
	{
		if (str[j] != '%')
			write (1, &str[j], 1);
		if (str[j] == '%')
		{
			j++;
			if (str[j] != '%')
			{
				str += j;
				return (str);
			}
			if (str[j] == '%')
				write (1, &str[j], 1);
		}
		j++;
	}
	str += j;
	return (str);
}

size_t	ft_printed_count(const char *str)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (str[i + j])
	{
		if (str[i + j] != '%')
			i++;
		if (str[i + j] == '%')
		{
			j++;
			if (str[i + j] != '%')
				j++;
			else
				i++;
		}
	}
	return (i);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	char	c;

	i = ft_printed_count(str);
	va_start(args, str);
	while (1)
	{
		str = ft_printfer(str);
		c = *str;
		if (c == 0)
		{
			va_end(args);
			return (i);
		}
		str++;
		i += ft_print_format(args, c);
	}
}
