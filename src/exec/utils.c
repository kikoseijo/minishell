/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 09:13:22 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/29 17:08:16 by cmac             ###   ########.fr       */
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

void	kill_childs(int *childs, int i, t_model *model)
{
	int		wstatus;
	char	*n_status;

	waitpid(childs[i], &wstatus, 0);
	n_status = ft_itoa(WEXITSTATUS(wstatus));
	set_env_value("?", n_status, model->env);
	free(n_status);
	while (--i >= 0)
	{
		if (childs[i] > 0)
			kill(childs[i], SIGKILL);
	}
}

void	setup_fdout(t_model *m, int i, t_pipes *pipes)
{
	int		t;
	t_cmd	*cmd;

	cmd = m->cmds[i];
	if (cmd->num_double_out > 0)
	{
		t = 0;
		while (t < cmd->num_double_out)
		{
			pipes->fdout = open(cmd->fd_double_out[t], O_WRONLY | O_APPEND);
			t++;
		}
	}
	else if (cmd->n_fdout > 0)
	{
		t = 0;
		while (t < cmd->n_fdout)
		{
			pipes->fdout = open(cmd->fd_out[t], O_WRONLY | O_CREAT | O_TRUNC,
					0664);
			t++;
		}
	}
	else
		pipes->fdout = dup(pipes->tmpout);
}
