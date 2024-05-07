/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 23:48:53 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/22 23:48:53 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current;
	int		i;

	if (lst == NULL)
		return (0);
	i = 1;
	current = lst;
	while (current->next != NULL)
	{
		current = current->next;
		i++;
	}
	return (i);
}
