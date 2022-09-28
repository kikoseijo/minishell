/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:53:59 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/28 21:59:15 by cmac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	exe_fdout(t_model *m, int i, t_pipes *pipes)
{
	int	fdpipe[2];

	if (i == m->n_cmd - 1)
	{
		if (m->outfile && ft_strlen(m->outfile_type) == 1)
			pipes->fdout = open(m->outfile,
								O_WRONLY | O_CREAT | O_TRUNC,
								0664);
		else if (m->outfile && ft_strlen(m->outfile_type) == 2)
			pipes->fdout = open(m->outfile, O_WRONLY | O_APPEND);
		else
			pipes->fdout = dup(pipes->tmpout);
		if (pipes->fdout < 0)
		{
			perror(m->outfile);
			return (-1);
		}
	}
	else
	{
		if (pipe(fdpipe) < 0)
			return (-1);
		pipes->fdout = fdpipe[1];
		pipes->fdin = fdpipe[0];
	}
	return (0);
}

static int	exe_cmd(t_model *model, int i, char ***envp)
{
	int		pid;
	t_cmd	*cmd;
	char	*cmd_path;

	cmd = model->cmds[i];
	if (exec_builtin(cmd, envp))
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		cmd_path = get_cmd(model->env_paths, cmd->args[0]);
		if (cmd == 0)
		{
			printf("%s: Command not found.\n", cmd->args[0]);
			return (-1);
		}
		execve(cmd_path, model->cmds[i]->args, *envp);
		printf("%s: Command not found.\n", cmd->args[0]);
		perror("execve");
		exit(1);
	}
	else if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	return (pid);
}

static int	exe_fdin(t_model *model, t_pipes *pipes)
{
	if (model->infile)
		pipes->fdin = open(model->infile, O_RDONLY);
	else
		pipes->fdin = dup(pipes->tmpin);
	if (pipes->fdin < 0)
	{
		perror(model->infile);
		close(pipes->tmpin);
		close(pipes->tmpout);
		return (-1);
	}
	return (0);
}

static int	exe_pipes(t_model *model, t_pipes *pipes, char **envp)
{
	int	i;
	int	ret;
	int	childs[256];

	i = 0;
	while (i < model->n_cmd)
	{
		dup2(pipes->fdin, 0);
		close(pipes->fdin);
		ret = exe_fdout(model, i, pipes);
		if (ret < 0)
			return (-1);
		dup2(pipes->fdout, 1);
		close(pipes->fdout);
		childs[i] = exe_cmd(model, i, &envp);
		i++;
	}
	kill_childs(childs, i - 1, model);
	return (0);
}

int	execute(t_model *model, char **envp)
{
	t_pipes	pipes;
	int		ret;

	pipes.tmpin = dup(0);
	pipes.tmpout = dup(1);
	ret = exe_fdin(model, &pipes);
	if (ret == -1)
		return (-1);
	ret = exe_pipes(model, &pipes, envp);
	dup2(pipes.tmpin, 0);
	dup2(pipes.tmpout, 1);
	close(pipes.tmpin);
	close(pipes.tmpout);
	waitpid(ret, NULL, 0);
	return (0);
}
