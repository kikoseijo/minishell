/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 08:47:01 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/23 13:16:37 by jseijo-p         ###   ########.fr       */
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

char		**g_envp;

void	free_model(t_model *model)
{
	int	i;

	i = model->n_cmd;
	while (i > 0)
	{
		i--;
		// ft_split_free(model->cmds[i]->args);
		// ft_split_free(model->cmds[i]->fd_simple_in);
		// ft_split_free(model->cmds[i]->fd_out);
		// ft_split_free(model->cmds[i]->fd_double_out);
		// ft_split_free(model->cmds[i]->heredocs_close);
		free(model->cmds[i]);
	}
	free(model->cmds);
	free((void *)model->infile);
	free(model);
}

static void	handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
		set_env_value("?", "1", &g_envp);
		set_env_value("_", "1", &g_envp);
	}
}

static int	check_exit(t_model *model, char *str)
{
	int	ret;

	if (!ft_strncmp(model->cmds[0]->args[0], "exit", 5))
	{
		ret = ft_exit(model);
		if (ret >= 0)
		{
			free(str);
			ft_split_free(g_envp);
			clear_history();
			system("leaks -q minishell");
			return (ret);
		}
	}
	return (-1);
}

int	main(int argc, char **argv, char **envp)
{
	t_model	*model;
	char	*str;
	int		ret;

	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	model = (t_model *)malloc(sizeof(t_model));
	model->env = &envp;
	while (1)
	{
		str = readline("\e[0;32m\U0000269B\e[0;94m prompt \U0001F498 $ \e[m");
		parser(str, model, envp);
		ret = check_exit(model, str);
		if (ret >= 0)
			return (ret);
		else
			execute(model, envp);
		free(str);
		free_model(model);
	}
	clear_history();
	ft_split_free(g_envp);
	return (0);
}
