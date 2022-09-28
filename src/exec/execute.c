/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:53:59 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/28 21:37:31 by cmac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	exe_fdout(t_model *m, int i, t_pipes *pipes)
{
	int	fdpipe[2];

	if (i == m->n_cmd - 1)
	{
		if (m->cmds[i]->num_double_out > 0)
			pipes->fdout = open(m->cmds[i]->fd_double_out[0],
								O_WRONLY | O_APPEND);
		else if (m->cmds[i]->n_fdout > 0)
			pipes->fdout = open(m->cmds[i]->fd_out[0],
								O_CREAT | O_RDWR | O_TRUNC,
								0644);
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

// static int	exe_cmd(t_cmd *cmd, char ***envp)
// {
// 	int	pid;
//
// 	if (exec_builtin(cmd, envp))
// 		return (-1);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		execve(get_path(cmd->args[0], *envp), cmd->args, *envp);
// 		printf("%s: Command not found.\n", cmd->args[0]);
// 		perror("execve");
// 		exit(1);
// 	}
// 	// else if (pid < 0)
// 	// {
// 	// 	perror("fork");
// 	// 	return (-1);
// 	// }
// 	return (pid);
// }

static int	exe_fdin(t_model *model, t_pipes *pipes)
{
	if (model->infile)
		pipes->fdin = open(model->infile, O_RDONLY);
	else
		pipes->fdin = dup(pipes->tmpin);
	/*
	** 	if (pipes->fdin < 0)
	** 	{
	** 		perror(model->infile);
	** 		close(pipes->tmpin);
	** 		close(pipes->tmpout);
	** 		return (-1);
	** 	}
	*/
	return (0);
}

// static void	kill_childs(int *childs, int i, t_model *model)
// {
// 	int		wstatus;
// 	char	*n_status;
//
// 	waitpid(childs[i], &wstatus, 0);
// 	n_status = ft_itoa(WEXITSTATUS(wstatus));
// 	set_env_value("?", n_status, model->env);
// 	free(n_status);
// 	while (--i >= 0)
// 	{
// 		if (childs[i] > 0)
// 			kill(childs[i], SIGKILL);
// 	}
// }

// static int	exe_pipes(t_model *model, t_pipes *pipes, char **envp)
// {
// 	int	i;
// 	int	ret;
// 	int	childs[256];
//
// 	i = 0;
// 	while (i < model->n_cmd)
// 	{
// 		dup2(pipes->fdin, 0);
// 		close(pipes->fdin);
// 		ret = exe_fdout(model, i, pipes);
// 		if (ret < 0)
// 		{
// 			printf("No output %s", model->cmds[i]->args[0]);
// 			return (-1);
// 		}
// 		dup2(pipes->fdout, 1);
// 		close(pipes->fdout);
// 		childs[i] = exe_cmd(model->cmds[i], &envp);
// 		i++;
// 	}
// 	// kill_childs(childs, i - 1, model);
// 	return (childs[i]);
// }

int	execute(t_model *model, char **envp)
{
	t_pipes	*pipes;
	int		ret;
	int		i;
	char	*cmd;

	pipes = (t_pipes *)malloc(sizeof(t_pipes));
	pipes->tmpin = dup(0);
	pipes->tmpout = dup(1);
	ret = exe_fdin(model, pipes);
	if (ret == -1)
		return (-1);
	i = 0;
	while (i < model->n_cmd)
	{
		dup2(pipes->fdin, 0);
		close(pipes->fdin);
		ret = exe_fdout(model, i, pipes);
		if (ret < 0)
		{
			printf("No output %s", model->cmds[i]->args[0]);
			return (-1);
		}
		dup2(pipes->fdout, 1);
		close(pipes->fdout);
		ret = fork();
		if (ret == 0)
		{
			cmd = get_cmd(model->env_paths, model->cmds[i]->args[0]);
			if (cmd == 0)
			{
				printf("%s: Command not found.\n", model->cmds[i]->args[0]);
				return (-1);
			}
			execve(cmd, model->cmds[i]->args, envp);
			printf("%s: Command not found.\n", model->cmds[i]->args[0]);
			perror("execve");
			exit(1);
		}
		i++;
	}
	dup2(pipes->tmpin, 0);
	dup2(pipes->tmpout, 1);
	close(pipes->tmpin);
	close(pipes->tmpout);
	waitpid(ret, NULL, 0);
	return (0);
}
