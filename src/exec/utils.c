/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 09:13:22 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/12/01 16:03:57 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_builtin(t_cmd *cmd)
{
	int	built;

	built = 1;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		ft_echo(cmd->num_args + 1, cmd->args);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		ft_unset(cmd->args[1]);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		ft_export(cmd->args[1]);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		ft_env(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
	{
		if (ft_cd(cmd->args[1]))
		{
			cmd->model->dollar = 1;
			return (built);
		}
	}
	else
		built = 0;
	cmd->model->dollar = 0;
	return (built);
}

static char	*find_cmd_in_path(char **paths, char *cmd)
{
	int		i;
	char	*res;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		res = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(res, F_OK | X_OK) == 0)
		{
			ft_free_array(paths);
			return (res);
		}
		free(res);
		i++;
	}
	ft_free_array(paths);
	return (0);
}

char	*get_cmd(char *cmd)
{
	char	**paths;

	if (ft_strchr(cmd, '/') && access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	paths = get_env_path();
	if (!paths)
		return (0);
	return (find_cmd_in_path(paths, cmd));
}

void	kill_childs(int *childs, int i, t_model *model)
{
	int		exit_int_code;
	int		exit_status_code;

	if (i < 0)
		return ;
	waitpid(childs[i], &exit_int_code, 0);
	exit_status_code = WEXITSTATUS(exit_int_code);
	if (exit_status_code)
		model->dollar = exit_status_code;
	else
		model->dollar = 0;
	while (--i >= 0)
	{
		if (childs[i] > 0)
			kill(childs[i], SIGKILL);
	}
}

void	setup_fdout(t_model *m, int i, t_pipes *pipes)
{
	t_cmd	*cmd;

	cmd = m->cmds[i];
	if (cmd->is_double_outfile != -1)
	{
		if (cmd->is_double_outfile == 1)
			pipes->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND,
					0664);
		else
			pipes->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC,
					0664);
	}
	else
		pipes->fdout = dup(pipes->tmpout);
}
