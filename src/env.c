/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:35:47 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/10/30 19:48:56 by jseijo-p         ###   ########.fr       */
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

void	set_env_value(char *key, char *value, char **envp)
{
	char	*tmp;
	char	*entry;
	int		size;

	if (!value)
		return ;
	size = (int)ft_strlen(key);
	tmp = (char *)ft_calloc(size + 2, sizeof(char));
	ft_strlcpy(tmp, key, size);
	ft_strlcat(tmp, "=", 1);
	entry = ft_strjoin(tmp, value);
	free(tmp);
	ft_unset(key, envp);
	ft_export(entry, envp);
	free(entry);
}

char	**get_env_path(char **envp)
{
	char	**path;
	char	*tmp;

	tmp = get_env_value((char *)"PATH", envp);
	if (!tmp)
		return (NULL);
	path = ft_split(tmp, ':');
	if (!path)
		return (NULL);
	return (path);
}

void	clear_terminal(void)
{
	int				index;
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	index = 0;
	while (w.ws_row != index)
	{
		printf("\n");
		index++;
	}
}

void	print_prompt(void)
{
	struct winsize	w;
	char			*cur_user;
	extern char		**environ;
	char			working_dir[256];

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	getcwd(working_dir, 256);
	cur_user = get_env_value((char *)"LOGNAME", environ);
	ft_putstr_fd((char *)"\e[0;34m", 1);
	ft_putstr_fd(cur_user, 1);
	ft_putstr_fd((char *)"\e[0;32m", 1);
	write(1, " in ", 4);
	ft_putstr_fd((char *)"\e[0;31m", 1);
	ft_putstr_fd(working_dir, 1);
	ft_putstr_fd((char *)"\n\e[1;32m", 1);
}
