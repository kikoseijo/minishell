/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 08:47:01 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/11/01 18:57:05 by cmac             ###   ########.fr       */
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

void	free_model(t_model *model, int with_env)
{
	int	i;

	i = model->n_cmd;
	while (i > 0)
	{
		i--;
		ft_free_array(model->cmds[i]->args);
		if (model->cmds[i]->num_heredocs > 0)
			ft_free_array(model->cmds[i]->heredocs_close);
		free(model->cmds[i]->infile);
		free(model->cmds[i]->outfile);
		free(model->cmds[i]->expansions);
		free(model->cmds[i]->scape_arguments);
		free(model->cmds[i]);
	}
	free(model->cmds);
	if (with_env == 1)
	{
		ft_free_array(global_envp);
		free(model);
	}
}

static void	handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		print_prompt();
		rl_redisplay();
		set_env_value((char *)"?", (char *)"1");
		set_env_value((char *)"_", (char *)"1");
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
			free_model(model, 1);
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
	global_envp = ft_array_join(environ, NULL);
	clear_terminal();
	while (1)
	{
		print_prompt();
		str = readline("$ ");
		parser(str, model);
		ret = check_exit(model);
		if (ret >= 0)
			return (ret);
		else
			execute(model);
		free_model(model, 0);
	}
	clear_history();
	return (0);
}
