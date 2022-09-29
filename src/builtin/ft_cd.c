/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:51:52 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/29 20:12:03 by cmac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cd(char *path, char ***envp)
{
	char	buffer[200];

	if (!path)
		path = get_env_value((char *)"HOME", *envp);
	if (!path)
		path = getenv("HOME");
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	set_env_value((char *)"OLDPWD", get_env_value((char *)"PWD", *envp), envp);
	getcwd(buffer, 200);
	set_env_value((char *)"PWD", buffer, envp);
	return (0);
}
