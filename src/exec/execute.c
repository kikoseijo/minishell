/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:53:59 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/11/02 20:55:30 by anramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	exe_fdout(t_model *m, int i, t_pipes *pipes)
{
	int	fdpipe[2];

	if (i == m->n_cmd - 1)
	{
		setup_fdout(m, i, pipes);
		if (pipes->fdout < 0)
		{
			perror(m->cmds[i]->outfile);
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

static int	exe_cmd(t_model *model, int i)
{
	int		pid;
	t_cmd	*cmd;
	char	*cmd_path;

	cmd = model->cmds[i];
	if (exec_builtin(cmd))
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		cmd_path = get_cmd(cmd->args[0]);
		if (cmd_path == 0)
		{
			printf("bash: %s: Command not found.\n", cmd->args[0]);
			exit(127);
		}
		execve(cmd_path, model->cmds[i]->args, g_envp);
		perror("execve");
		exit(1);
	}
	else if (pid < 0)
		return (-1);
	return (pid);
}

static int	exe_fdin(t_model *model, t_pipes *pipes)
{
	int	i;

	i = -1;
	while (++i < model->n_cmd)
	{
		if (model->cmds[i]->infile)
			pipes->fdin = open(model->cmds[i]->infile, O_RDONLY);
		else
			pipes->fdin = dup(pipes->tmpin);
	}
	if (pipes->fdin < 0)
	{
		perror(model->cmds[i]->infile);
		close(pipes->tmpin);
		close(pipes->tmpout);
		return (-1);
	}
	return (0);
}

static int	exe_pipes(t_model *model, t_pipes *pipes)
{
	int	i;
	int	ret;
	int	*childs;

	i = 0;
	childs = (int *)ft_calloc(model->n_cmd + 1, sizeof(int));
	while (i < model->n_cmd)
	{
		dup2(pipes->fdin, 0);
		close(pipes->fdin);
		ret = exe_fdout(model, i, pipes);
		if (ret < 0)
			return (-1);
		dup2(pipes->fdout, 1);
		close(pipes->fdout);
		childs[i] = exe_cmd(model, i);
		i++;
	}
	kill_childs(childs, i - 1);
	free(childs);
	return (0);
}

int	execute(t_model *model)
{
	t_pipes	pipes;
	int		ret;

	pipes.tmpin = dup(0);
	pipes.tmpout = dup(1);
	ret = exe_fdin(model, &pipes);
	if (ret == -1)
		return (-1);
	ret = exe_pipes(model, &pipes);
	dup2(pipes.tmpin, 0);
	dup2(pipes.tmpout, 1);
	close(pipes.tmpin);
	close(pipes.tmpout);
	waitpid(ret, NULL, 0);
	return (0);
}
