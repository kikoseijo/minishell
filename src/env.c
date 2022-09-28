/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:35:47 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/28 22:00:21 by cmac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_env_value(char *key, char ***envp)
{
	int	i;
	int	len_key;

	len_key = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(*envp[i], key, len_key) && *envp[i][len_key] == '=')
			return (envp[i][len_key + 1]);
		i++;
	}
	return (NULL);
}

void	set_env_value(char *key, char *value, char ***envp)
{
	char	key_eq[100];
	char	*entry;

	if (!value)
		return ;
	ft_strlcpy(key_eq, key, 100);
	ft_strlcat(key_eq, "=", 100);
	entry = ft_strjoin(key_eq, value);
	ft_unset(key, envp);
	ft_export(entry, envp);
	free(entry);
}
