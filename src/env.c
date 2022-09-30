/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:35:47 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/30 17:30:00 by jseijo-p         ###   ########.fr       */
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

char	*get_env_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
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
