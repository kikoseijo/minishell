/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:54:23 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/30 09:00:52 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_new_size(char *str, char ***envp)
{
	int		count;
	char	**ptr;
	int		size;

	count = 0;
	ptr = *envp;
	while (*ptr)
	{
		if (!ft_strncmp(*ptr, str,
				ft_strlen(str)) && (*ptr)[ft_strlen(str)] == '=')
			count++;
		ptr++;
	}
	size = ft_array_len(*envp) - count;
	if (size <= 0)
		return (0);
	return (size);
}

static int	del_str_split(char *str, char ***envp)
{
	int		size;
	char	**ptr;
	char	**new_tab;
	int		i;

	size = get_new_size(str, envp);
	if (!size)
		return (0);
	new_tab = (char **)malloc(sizeof(char *) * (size + 1));
	ptr = *envp;
	i = 0;
	while (*ptr)
	{
		if (!(!ft_strncmp(*ptr, str,
					ft_strlen(str)) && (*ptr)[ft_strlen(str)] == '='))
			new_tab[i++] = ft_strdup(*ptr);
		ptr++;
	}
	new_tab[i] = NULL;
	*envp = new_tab;
	return (0);
}

void	ft_unset(char *input, char ***envp)
{
	del_str_split(input, envp);
}
