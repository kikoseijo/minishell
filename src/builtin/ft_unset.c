/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:54:23 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/11/02 21:06:26 by anramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_new_size(char *str)
{
	int		count;
	char	**ptr;
	int		size;

	count = 0;
	ptr = g_envp;
	while (*ptr)
	{
		if (!ft_strncmp(*ptr, str, ft_strlen(str))
			&& (*ptr)[ft_strlen(str)] == '=')
			count++;
		ptr++;
	}
	size = ft_array_len(g_envp) - count;
	if (size <= 0)
	{
		free(g_envp);
		g_envp = NULL;
		return (0);
	}
	return (size);
}

void	ft_unset(char *str)
{
	int		size;
	char	**tmp;
	char	**res;
	int		i;

	size = get_new_size(str);
	if (!size)
		return ;
	res = (char **)ft_calloc(size + 1, sizeof(char *));
	tmp = g_envp;
	i = 0;
	while (*tmp)
	{
		if (!((*tmp)[ft_strlen(str)] == '=' && !ft_strncmp(*tmp, str,
				ft_strlen(str))))
		{
			res[i] = ft_strdup(*tmp);
			i++;
		}
		tmp++;
	}
	ft_free_array(g_envp);
	g_envp = res;
}
