/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:16:59 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/21 18:48:23 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc(3)) and returns an array
** of strings obtained by splitting ’s’ using the
** character ’c’ as a delimiter. The array must end
** with a NULL pointer.
*/

#include "../../inc/libft.h"

static char	**get_words(char *str, unsigned int len, int word_count)
{
	char			**res;
	unsigned int	i;
	unsigned int	w;

	res = (char **)ft_calloc(word_count + 1, sizeof(char *));
	if (res == 0)
		return (0);
	i = 0;
	w = 0;
	if (str[i] != '\0')
		res[w++] = ft_strdup(&str[i]);
	i++;
	while (i < len)
	{
		if (str[i] != '\0' && str[i - 1] == '\0')
			res[w++] = ft_strdup(&str[i]);
		i++;
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	len;
	unsigned int	i;
	int				word_count;
	char			*str;
	char			**res;

	len = ft_strlen(s);
	str = ft_strdup(s);
	if (str == 0)
		return (0);
	word_count = 0;
	i = 0;
	while (i < len)
	{
		if (str[i] == c)
			str[i] = '\0';
		else if (i == 0 || str[i - 1] == '\0')
			word_count++;
		i++;
	}
	res = get_words(str, len, word_count);
	free(str);
	return (res);
}
