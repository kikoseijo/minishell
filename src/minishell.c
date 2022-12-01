/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 08:47:01 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/12/01 17:24:13 by jseijo-p         ###   ########.fr       */
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

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		print_prompt();
		rl_redisplay();
		set_env_value((char *)"_", (char *)"1");
	}
}

void	init(t_model **model, char **environ)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	(*model) = (t_model *)malloc(sizeof(t_model));
	(*model)->n_cmd = 0;
	g_envp = ft_array_join(environ, NULL);
	clear_terminal();
}

void	free_model(t_model *model, int with_env)
{
	int	i;

	i = model->n_cmd;
	while (i > 0)
	{
		i--;
		ft_free_array(model->cmds[i]->args);
		ft_free_array(model->cmds[i]->heredocs_close);
		free(model->cmds[i]->infile);
		free(model->cmds[i]->outfile);
		free(model->cmds[i]->expansions);
		free(model->cmds[i]->scape_arguments);
		free(model->cmds[i]);
	}
	if (model->n_cmd > 0)
		free(model->cmds);
	if (with_env == 1)
	{
		ft_free_array(g_envp);
		free(model);
	}
}

static int	check_exit(t_model *model)
{
	int	ret;

	if (model->cmds[0]->num_args < 0 || !model->cmds[0]->args[0])
		return (-1);
	if (!ft_strncmp(model->cmds[0]->args[0], "exit", 5))
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

	init(&model, environ);
	while (1)
	{
		print_prompt();
		str = readline("$ ");
		if (str == NULL && ft_strlen(str) == 0)
			exit(-1);
		if (str != NULL && ft_strlen(str) > 0 && check_empty_spaces(str) != -1)
		{
			parser(str, model);
			ret = check_exit(model);
			if (ret >= 0)
				return (ret);
			execute(model);
			free_model(model, 0);
		}
	}
	clear_history();
	return (0);
}
