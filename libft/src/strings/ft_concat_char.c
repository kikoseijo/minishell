/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:57:10 by anramire          #+#    #+#             */
/*   Updated: 2022/10/03 20:48:24 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_concat_char(char *str, char c)
{
	int		len;
	char	*dup;
	int		i;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	dup = (char *)ft_calloc((len + 2), sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = c;
	free(str);
	return (dup);
}
