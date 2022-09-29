/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:35:47 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/29 20:13:41 by cmac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_env_value(char *key, char **envp)
{
	int	i;
	int	len;

	len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, len) && envp[i][len] == '=')
			return (&envp[i][len + 1]);
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
