/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 08:47:01 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/10/10 17:00:08 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
** Allowed external functions:
** readline, rl_clear_history, rl_on_new_line,
** rl_replace_line, rl_redisplay, add_history,
** printf, malloc, free, write, access, open, read,
** close, fork, wait, waitpid, wait3, wait4, signal,
** sigaction, sigemptyset, sigaddset, kill, exit,
** getcwd, chdir, stat, lstat, fstat, unlink, execve,
** dup, dup2, pipe, opendir, readdir, closedir,
** strerror, perror, isatty, ttyname, ttyslot, ioctl,
** getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
** tgetnum, tgetstr, tgoto, tputs
*/

void	free_model(t_model *model)
{
	int	i;

	i = model->n_cmd;
	while (i-- > 0 && model->cmds[i])
	{
		ft_split_free(model->cmds[i]->args);
		if (model->cmds[i]->infile != NULL)
			free(model->cmds[i]->infile);
		if (model->cmds[i]->outfile != NULL)
			free(model->cmds[i]->outfile);
		ft_split_free(model->cmds[i]->heredocs_close);
		free(model->cmds[i]->expansions);
		free(model->cmds[i]->scape_arguments);
		free(model->cmds[i]);
	}
	free(model->cmds);
	// free(model->env);
	free(model);
}

static void	handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		print_prompt();
		rl_redisplay();
		exit(-1);
	}
}

static int	check_exit(t_model *model)
{
	int	ret;

	if (!ft_strncmp(model->cmds[0]->args[0], "exit", 4))
	{
		ret = ft_exit(model);
		if (ret >= 0)
		{
			clear_history();
			system("leaks -q minishell");
			return (ret);
		}
	}
	return (-1);
}

int	main(void)
{
	t_model		*model;
	extern char	**environ;
	char		*str;
	int			ret;

	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	model = (t_model *)malloc(sizeof(t_model));
	model->env = &environ;
	clear_terminal();
	while (1)
	{
		print_prompt();
		str = readline("$ ");
		parser(str, model, *model->env);
		ret = check_exit(model);
		if (ret >= 0)
			return (ret);
		else
			execute(model);
	}
	clear_history();
	return (0);
}
