/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 09:13:22 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/10/10 16:53:05 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_builtin(t_cmd *cmd, char ***envp)
{
	int	built;

	built = 1;
	if (!ft_strncmp("echo", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_echo(cmd->num_args + 1, cmd->args);
	else if (!ft_strncmp("unset", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_unset(cmd->args[1], envp);
	else if (!ft_strncmp("export", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_export(cmd->args[1], envp);
	else if (!ft_strncmp("env", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_env(*envp);
	else if (!ft_strncmp("pwd", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_pwd();
	else if (!ft_strncmp("cd", cmd->args[0], ft_strlen(cmd->args[0])))
	{
		if (ft_cd(cmd->args[1], envp))
		{
			set_env_value((char *)"?", (char *)"1", envp);
			return (built);
		}
	}
	else
		built = 0;
	set_env_value((char *)"?", (char *)"0", envp);
	return (built);
}

char	*get_cmd(t_model *model, char *cmd)
{
	char	*res;
	char	**paths;

	if (ft_strchr(cmd, '/') && access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	paths = get_env_path(*model->env);
	if (!paths)
		return (0);
	while (*paths)
	{
		res = ft_strjoin(*paths, "/");
		res = ft_strjoin(res, cmd);
		if (access(res, F_OK | X_OK) == 0)
			return (res);
		free(res);
		paths++;
	}
	return (0);
}

void	kill_childs(int *childs, int i, t_model *model)
{
	int		exit_int_code;
	char	*exit_str_code;

	waitpid(childs[i], &exit_int_code, 0);
	exit_str_code = ft_itoa(WEXITSTATUS(exit_int_code));
	set_env_value((char *)"?", exit_str_code, model->env);
	free(exit_str_code);
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
		if (cmd->is_double_outfile == 0)
			pipes->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND,
					0664);
		else
			pipes->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC,
					0664);
	}
	else
		pipes->fdout = dup(pipes->tmpout);
}
