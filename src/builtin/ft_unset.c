/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:54:23 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/10/30 13:49:09 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_new_size(char *str, char **envp)
{
	int	count;
	int	size;

	count = 0;
	while (*envp)
	{
		if (!ft_strncmp(*envp, str, ft_strlen(str))
			&& (*envp)[ft_strlen(str)] == '=')
			count++;
		envp++;
	}
	size = ft_array_len(envp) - count;
	if (size <= 0)
		return (0);
	return (size);
}

static int	del_str_split(char *str, char ***envp)
{
	int		size;
	char	**tmp;
	char	**new_env;
	int		i;

	size = get_new_size(str, *envp);
	if (!size)
		return (0);
	new_env = (char **)ft_calloc(size + 1, sizeof(char *));
	tmp = *envp;
	i = 0;
	while (*tmp)
	{
		if (!(!ft_strncmp(*tmp, str, ft_strlen(str))
				&& (*tmp)[ft_strlen(str)] == '='))
			new_env[i++] = ft_strdup(*tmp);
		tmp++;
	}
	ft_split_free(*envp);
	*envp = new_env;
	return (0);
}

void	ft_unset(char *input, char **envp)
{
	del_str_split(input, &envp);
}
