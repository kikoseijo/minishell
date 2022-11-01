/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:54:23 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/11/01 18:49:30 by cmac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_new_size(char *str)
{
	int		count;
	char	**ptr;
	int		size;

	count = 0;
	ptr = global_envp;
	while (*ptr)
	{
		if (!ft_strncmp(*ptr, str, ft_strlen(str))
			&& (*ptr)[ft_strlen(str)] == '=')
			count++;
		ptr++;
	}
	size = ft_array_len(global_envp) - count;
	if (size <= 0)
	{
		free(global_envp);
		global_envp = NULL;
		return (0);
	}
	return (size);
}

static void	ft_array_splice(char *str)
{
	int		size;
	char	**tmp;
	char	**new_env;
	int		i;

	size = get_new_size(str);
	if (!size)
		return ;
	new_env = (char **)ft_calloc(size + 1, sizeof(char *));
	tmp = global_envp;
	i = 0;
	while (*tmp)
	{
		if (!(!ft_strncmp(*tmp, str, ft_strlen(str))
				&& (*tmp)[ft_strlen(str)] == '='))
		{
			new_env[i] = ft_strdup(*tmp);
			i++;
		}
		tmp++;
	}
	ft_free_array(global_envp);
	global_envp = new_env;
}

void	ft_unset(char *input)
{
	ft_array_splice(input);
}
