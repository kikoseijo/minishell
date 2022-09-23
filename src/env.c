/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:35:47 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/23 12:48:23 by jseijo-p         ###   ########.fr       */
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

static char	*check_dir(char *cmd, char **paths, int i)
{
	DIR				*dir;
	struct dirent	*file;
	char			*tmp;
	char			*ret;

	dir = opendir(paths[i]);
	file = readdir(dir);
	while (file)
	{
		if (!ft_strncmp(file->d_name, cmd, ft_strlen(cmd) + 1))
		{
			tmp = ft_strjoin(paths[i], "/");
			ret = ft_strjoin(tmp, cmd);
			free(tmp);
			closedir(dir);
			ft_split_free(paths);
			return (ret);
		}
		file = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}

static char	*relative_path(char *cmd)
{
	char	pwd_buf[150];
	int		len;

	getcwd(pwd_buf, 150);
	len = ft_strlen(pwd_buf);
	if (len > 148)
		return (NULL);
	pwd_buf[len + 1] = '\0';
	pwd_buf[len] = '/';
	return (ft_strjoin(pwd_buf, cmd));
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*ret;
	int		i;

	if (*cmd == '/')
		return (cmd);
	if (*cmd == '.')
		return (relative_path(cmd));
	paths = ft_split(get_env_value((char *)"PATH", &envp), ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		ret = check_dir(cmd, paths, i);
		if (ret)
			return (ret);
	}
	ft_split_free(paths);
	return (NULL);
}
