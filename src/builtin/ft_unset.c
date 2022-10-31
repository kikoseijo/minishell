/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:54:23 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/10/31 21:48:38 by cmac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	find_env_position(char *str, char ***envp)
{
	char	**ptr;
	int		count;
	int		res;

	ptr = *envp;
	count = 0;
	while (*ptr)
	{
		if (!ft_strncmp(*ptr, str, ft_strlen(str))
			&& (*ptr)[ft_strlen(str)] == '=')
			count++;
		ptr++;
	}
	res = ft_array_len(*envp) - count;
	if (res <= 0)
		return (0);
	return (res);
}

static int	del_str_split(char *str, char ***envp)
{
	int		pos;
	char	**tmp;
	char	**res;
	int		i;

	pos = find_env_position(str, envp);
	if (!pos)
		return (0);
	res = (char **)ft_calloc(ft_array_len(*envp) + 1, sizeof(char *));
	tmp = *envp;
	i = 0;
	while (*tmp)
	{
		if (!(!ft_strncmp(*tmp, str, ft_strlen(str))
				&& (*tmp)[ft_strlen(str)] == '='))
		{
			res[i] = ft_strdup(*tmp);
			i++;
		}
		tmp++;
	}
	ft_free_array(*envp);
	*envp = res;
	return (0);
}

void	ft_unset(char *input, char ***envp)
{
	del_str_split(input, envp);
}
