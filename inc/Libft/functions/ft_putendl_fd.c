/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 20:06:01 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/16 20:06:01 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putendl_fd(char *str, int fd)
{
	size_t	i;
	char	c;

	c = '\n';
	i = 0;
	while (str[i])
	{
		write (fd, &str[i], 1);
		i++;
	}
	write (fd, &c, 1);
}
