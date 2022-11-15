/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:29:54 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/05/12 15:23:54 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Deletes and frees the given node and every
** successor of that node, using the function ’del’
** and free(3).
** Finally, the pointer to the list must be set to
** NULL.
**
** External functs. free
*/

#include "../../inc/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*nlst;

	nlst = *lst;
	while (nlst)
	{
		tmp = nlst->next;
		ft_lstdelone(nlst, del);
		nlst = tmp;
	}
	*lst = NULL;
}
