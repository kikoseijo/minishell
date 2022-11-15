/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:31:35 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/05/12 15:23:54 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Iterates the list ’lst’ and applies the function
** ’f’ on the content of each node. Creates a new
** list resulting of the successive applications of
** the function ’f’. The ’del’ function is used to
** delete the content of a node if needed.
**
** External functs. malloc, free
*/

#include "../../inc/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;

	if (!lst || !f)
		return (NULL);
	new_list = ft_lstnew(f(lst->content));
	if (!new_list)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			break ;
		}
		lst = lst->next;
		ft_lstadd_back(&new_list, new_node);
	}
	return (new_list);
}
