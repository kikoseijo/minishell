/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:53:59 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/21 20:08:00 by anramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_cmd(char **paths, char *cmd)
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

static void	exe_fds(t_model *m, int i, int tmpout, int fdin)
{
	int	t;
	int	fdout;
	int	fdpipe[2];

	if (i == m->n_cmd - 1)
	{
		if (m->cmds[i]->n_fdout > 0)
		{
			t = 0;
			while (t < m->cmds[i]->n_fdout)
				fdout = open(m->cmds[i]->fd_out[t++], O_CREAT | O_RDWR, 0644);
		}
		else
			fdout = dup(tmpout);
	}
	else
	{
		pipe(fdpipe);
		fdout = fdpipe[1];
		fdin = fdpipe[0];
	}
	dup2(fdout, 1);
	close(fdout);
}

static int	exe_cmd(t_model *m, char **envp, int i)
{
	int		res;
	char	*cmd;

	res = fork();
	if (res == 0)
	{
		cmd = get_cmd(m->env_paths, m->cmds[i]->args[0]);
		if (cmd == 0)
		{
			printf("%s: Command not found.\n", m->cmds[i]->args[0]);
			return (-1);
		}
		execve(cmd, m->cmds[i]->args, envp);
		perror("execve");
		exit(1);
	}
	return (res);
}

void	exe_close_and_wait(int ret, int tmpin, int tmpout)
{
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	waitpid(ret, NULL, 0);
}

void	execute(t_model *model, char **envp)
{
	int	tmpin;
	int	tmpout;
	int	fdin;
	int	ret;
	int	i;
	
	if(model == NULL){
		ft_printf("traza\n");
		return ;
	}
	tmpin = dup(0);
	tmpout = dup(1);
	if (model->infile)
		fdin = open(model->infile, O_RDONLY);
	else
		fdin = dup(tmpin);
	i = 0;
	while (i < model->n_cmd)
	{
		dup2(fdin, 0);
		close(fdin);
		exe_fds(model, i, tmpout, fdin);
		ret = exe_cmd(model, envp, i);
		i++;
	}
	exe_close_and_wait(ret, tmpin, tmpout);
}
