/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:50:19 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/10/30 20:28:46 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_split_free(char **split)
{
	char	**temp;

	if (!split)
		return ;
	temp = split;
	while (*split)
	{
		free(*split);
		split++;
	}
	free(*split);
	free(temp);
}
