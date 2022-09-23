/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:51:52 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/23 09:38:22 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cd(char *path, char ***envp)
{
	char	buffer[256];

	if (!path)
		path = get_env_value((char *)"HOME", envp);
	if (!path)
		path = getenv("HOME");
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	set_env_value((char *)"OLDPWD", get_env_value((char *)"PWD", envp), envp);
	getcwd(buffer, 256);
	set_env_value((char *)"PWD", buffer, envp);
	return (0);
}
