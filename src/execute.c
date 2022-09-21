/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:53:59 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/21 10:49:13 by jseijo-p         ###   ########.fr       */
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

void	execute(t_model *model, char **envp)
{
	int		tmpin;
	int		tmpout;
	int		fdin;
	int		ret;
	int		fdout;
	int		i;
	int		t;
	char	*cmd;
	int		fdpipe[2];

	tmpin = dup(0);
	tmpout = dup(1);
	if (model->infile)
		fdin = open(model->infile, O_RDONLY);
	else
		fdin = dup(tmpin);
	i = 0;
	while (i < model->num_commands)
	{
		// redirect input
		dup2(fdin, 0);
		close(fdin);
		if (i == model->num_commands - 1)
		{
			if (model->commands[i]->num_simple_out > 0)
			{
				t = 0;
				while (t < model->commands[i]->num_simple_out)
				{
					// TODO: Revisar lo del O_TRUNC
					fdout = open(model->commands[i]->fd_simple_out[t],
									O_CREAT | O_RDWR | O_TRUNC,
									0644);
					t++;
				}
			}
			else
			{
				fdout = dup(tmpout);
			}
		}
		else
		{
			// Not last simple command create pipe.
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		// Redirect output
		dup2(fdout, 1);
		close(fdout);
		// Create child process
		ret = fork();
		if (ret == 0)
		{
			cmd = get_cmd(model->env_paths, model->commands[i]->args[0]);
			if (cmd == 0)
			{
				printf("%s: Command not found.\n", model->commands[i]->args[0]);
				return ;
			}
			execve(cmd, model->commands[i]->args, envp);
			// execvp(model->commands[i]->command, model->commands[i]->args);
			perror("execve");
			exit(1);
		}
		i++;
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	waitpid(ret, NULL, 0);
}
