/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 08:47:01 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/29 20:28:01 by cmac             ###   ########.fr       */
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
	while (i > 0)
	{
		i--;
		free(model->cmds[i]);
	}
	free(model->cmds);
	free(model);
}

static void	handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		exit(-1);
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
			clear_history();
			return (ret);
		}
	}
	return (-1);
}
// system("leaks -q minishell");

static char	*get_env_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
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
	model->env_paths = ft_split(get_env_path(environ), ':');
	while (1)
	{
		str = readline("\e[0;32m\U0000269B\e[0;94m prompt \U0001F498 $ \e[m");
		parser(str, model, *model->env);
		ret = check_exit(model, str);
		if (ret >= 0)
			return (ret);
		else
			execute(model, model->env);
	}
	clear_history();
	return (0);
}
