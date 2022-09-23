/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:53:59 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/23 11:34:22 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	exe_fds(t_model *m, int i, t_pipes *pipes)
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

static int	exe_cmd(t_cmd *cmd, char ***envp)
{
	int	pid;

	if (exec_builtin(cmd, envp))
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		execve(get_path(cmd->args[0], *envp), cmd->args, *envp);
		printf("command not found: %s\n", cmd->args[0]);
		exit(-1);
	}
	else if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	return (pid);
}

static int	exe_fdin(t_model *model, t_pipes pipes)
{
	if (model->infile)
		pipes.fdin = open(model->infile, O_RDONLY);
	else
		pipes.fdin = dup(pipes.tmpin);
	if (pipes.fdin < 0)
	{
		perror(model->infile);
		close(pipes.tmpin);
		close(pipes.tmpout);
		return (-1);
	}
	return (0);
}

static void	kill_childs(int *childs, int i, t_model *model)
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

static int	exe_pipes(t_model *model, t_pipes *pipes, char **envp)
{
	int	i;
	int	ret;
	int	childs[1024];

	i = 0;
	while (i < model->n_cmd)
	{
		dup2(pipes->fdin, 0);
		close(pipes->fdin);
		ret = exe_fds(model, i, pipes);
		if (ret < 0)
			return (-1);
		dup2(pipes->fdout, 1);
		close(pipes->fdout);
		childs[i] = exe_cmd(model->cmds[i], &envp);
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
	ret = exe_fdin(model, pipes);
	if (ret == -1)
		return (-1);
	ret = exe_pipes(model, &pipes, envp);
	dup2(pipes.tmpin, 0);
	dup2(pipes.tmpout, 1);
	close(pipes.tmpin);
	close(pipes.tmpout);
	// waitpid(ret, NULL, 0);
}
