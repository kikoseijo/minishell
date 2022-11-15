/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:25:11 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/06/15 11:44:46 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc(3)) and returns a new node.
** The member variable ’content’ is initialized with
** the value of the parameter ’content’. The variable
** ’next’ is initialized to NULL.
*/

#include "../../inc/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*res;

	res = (t_list *)malloc(sizeof(t_list));
	if (!res)
		return (res = NULL);
	res->content = content;
	res->next = NULL;
	return (res);
}
