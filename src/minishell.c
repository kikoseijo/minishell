/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 08:47:01 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/21 19:11:09 by anramire         ###   ########.fr       */
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
		ft_split_free(model->cmds[i]->args);
		ft_split_free(model->cmds[i]->fd_simple_in);
		ft_split_free(model->cmds[i]->fd_out);
		ft_split_free(model->cmds[i]->fd_double_out);
		ft_split_free(model->cmds[i]->heredocs_close);
		free(model->cmds[i]);
	}
	free(model->cmds);
	free((void *)model->infile);
	free(model);
}

static void	print_terminal(void)
{
	int				index;
	struct winsize	w;
	char			working_dir[150];

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	index = 0;
	while (w.ws_col != index)
	{
		write(1, "─", 3);
		index++;
	}
	write(1, "\n", 1);
	getcwd(working_dir, 150);
	ft_putstr_fd("\e[1;35m", 1);
	ft_putstr_fd(working_dir, 1);
	ft_putstr_fd("\n\e[0;37m", 1);
}

static void	handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		print_terminal();
		rl_redisplay();
		// set_env_value("?", "1", &g_envp);
		// set_env_value("_", "1", &g_envp);
	}
}

static char	*get_env_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

int	main(int argc, char **argv, char **envp)
{
	t_model	*model;
	char	*str;

	//Provisional hasta que este corregido el handler
	//signal(SIGINT, handler);
	//signal(SIGQUIT, SIG_IGN);
	model = (t_model *)malloc(sizeof(t_model));
	model->env_paths = ft_split(get_env_path(envp), ':');
	while (1)
	{
		print_terminal();
		str = readline("\e[0;32m\U0000269B\e[0;94m prompt \U0001F498 $ \e[m");
		parser(str, model, envp);
		execute(model, envp);
	}
	return (0);
}
