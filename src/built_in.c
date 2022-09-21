/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:50:24 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/21 17:26:14 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
** void	ft_pwd(void)
** {
** 	char	buffer[200];
**
** 	getcwd(buffer, 200);
** 	printf("%s\n", buffer);
** }
*/

int	ft_exit(t_model *model)
{
	int	ret;

	if (model->cmds[0]->num_args > 2)
	{
		ft_putstr_fd((char *)"exit: too many arguments\n", 2);
		return (-1);
	}
	else if (model->cmds[0]->args[1] == NULL)
	{
		free_model(model);
		return (0);
	}
	else if (ft_str_is_numeric(model->cmds[0]->args[1]))
	{
		ret = ft_atoi(model->cmds[0]->args[1]);
		return ((int)((unsigned char)ret));
	}
	else
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return (-1);
	}
}

int	ft_cd(char *path, char **envp)
{
	char	buffer[200];

	if (!path)
		path = get_env_value("HOME", envp);
	if (!path)
		path = getenv("HOME");
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	set_env_value("OLDPWD", get_env_value("PWD", envp), envp);
	getcwd(buffer, 200);
	set_env_value("PWD", buffer, envp);
	return (0);
}
