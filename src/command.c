/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:53:59 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/19 20:05:03 by anramire         ###   ########.fr       */
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

void execute(t_model *model, char **envp)
{
	int tmpin;
	int tmpout;
	int fdin;
	int ret;
	int fdout;
	int i;
	int t;
	char	*cmd;

	tmpin = dup(0);
	tmpout = dup(1);
	if(model->infile)
		fdin = open(model->infile, O_RDONLY);
	else
		fdin = dup(tmpin);
	i = 0;
	while(i<model->num_commands)
	{
		// redirect input
		dup2(fdin, 0);
		close(fdin);
		if(i == model->num_commands - 1)
		{
			if(model->commands[i]->num_simple_out>0)
			{
				t = 0;
				while(t < model->commands[i]->num_simple_out)
				{
					// TODO: Revisar lo del O_TRUNC
					fdout = open(model->commands[i]->fd_simple_out[t], \
						O_CREAT | O_RDWR | O_TRUNC, 0644);
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
			int fdpipe[2];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}

		// Redirect output
		dup2(fdout, 1);
		close(fdout);

		// Create child process
		ret = fork();
		if(ret == 0)
		{
			cmd = get_cmd(model->env_paths, model->commands[i]->args[0]);
			if(cmd == 0)
			{
				printf("%s: Command not found.\n", model->commands[i]->args[0]);
				return;
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

void execute_simple_DEPRECATED(t_model *model)
{
	int ret;
	int i;

	i = 0;
	while ( i < model->num_commands )
	{
		ret = fork();
		if (ret == 0) {
			//child

			execvp(model->commands[i]->args[0], model->commands[i]->args);
			perror("execvp");
			_exit(1);
		}
		else if (ret < 0)
		{
			perror("fork");
			return;
		}
		i++;
		// Parent shell continue
	} // for
	if (!model->background)
	{
		// wait for last process
		waitpid(ret, NULL, 0);
	}
}

void clear()
{

}

/*
** The constructor C​ommand::Command(​) constructs and empty command that will
** be populated with the method
** Command::i​nsertSimpleCommand(SimpleCommand* simpleCommand).​insertSimpleCommand
** also enlarges the array _simpleCommands if necessary.
** The variables _outFile, _inputFile, _errFile will be NULL if
** no redirection was done, or the name of the file they are being redirected
**< to.
*/



void insert_simple_command( t_simple_command *simpleCommand )
{

}
