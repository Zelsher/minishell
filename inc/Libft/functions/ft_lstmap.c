/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:01:09 by eboumaza          #+#    #+#             */
/*   Updated: 2023/08/24 17:01:09 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*current;

	if (!lst || !f || !del)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	current = new;
	while (lst && current && lst->next)
	{
		lst = lst->next;
		current->next = ft_lstnew(f(lst->content));
		current = current->next;
	}
	return (new);
}
