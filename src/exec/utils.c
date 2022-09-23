/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 09:13:22 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/23 15:29:07 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_builtin(t_cmd *cmd, char ***envp)
{
	int	built;

	built = 1;
	if (!ft_strncmp("echo", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_echo(cmd->num_args, cmd->args);
	else if (!ft_strncmp("cd", cmd->args[0], ft_strlen(cmd->args[0])))
	{
		if (ft_cd(cmd->args[1], envp))
		{
			set_env_value("?", "1", envp);
			return (built);
		}
	}
	else if (!ft_strncmp("pwd", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_pwd();
	else if (!ft_strncmp("export", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_export(cmd->args[1], envp);
	else if (!ft_strncmp("unset", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_unset(cmd->args[1], envp);
	else if (!ft_strncmp("env", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_env(*envp);
	else
		built = 0;
	set_env_value("?", "0", envp);
	return (built);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*res;

	if (ft_strchr(cmd, '/') && access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		res = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(res, F_OK | X_OK) == 0)
			return (res);
		free(res);
		paths++;
	}
	return (0);
}

int	len_table(char **table)
{
	int	len;

	len = 0;
	while (table && table[len])
		len++;
	return (len);
}

char	**join_split(char **a, char **b)
{
	int		size;
	char	**ret;
	int		i;
	int		j;

	size = len_table(a) + len_table(b) + 1;
	ret = (char **)malloc(size * sizeof(char *));
	if (!ret)
		return (NULL);
	i = -1;
	while (a && a[++i])
		ret[i] = ft_strdup(a[i]);
	j = 0;
	while (b && b[j])
		ret[i++] = ft_strdup(b[j++]);
	ret[i] = NULL;
	return (ret);
}
