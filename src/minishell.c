/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 08:47:01 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/10/30 20:38:57 by jseijo-p         ###   ########.fr       */
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

char		**global_envp;

void	free_model(t_model *model)
{
	int	i;

	//
	i = model->n_cmd;
	// printf("KKKKK\n");
	while (i > 0)
	{
		i--;
		printf("1KKKKK\n");
		ft_split_free(model->cmds[i]->args);
		// printf("2KKKKK\n");
		ft_split_free(model->cmds[i]->heredocs_close);
		printf("3KKKKK\n");
		free(model->cmds[i]->infile);
		free(model->cmds[i]->outfile);
		free(model->cmds[i]->expansions);
		free(model->cmds[i]->scape_arguments);
		// free(model->cmds[i]);
		printf("5KKKKK\n");
		printf("HELLLOOOOOO\n");
	}
	printf("333HELLLOOOOOO\n");
	free(model->cmds);
	ft_split_free(model->env);
	free(model);
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
		set_env_value((char *)"?", (char *)"1", global_envp);
		set_env_value((char *)"_", (char *)"1", global_envp);
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
			printf("[ret]:%d\n", ret);
			clear_history();
			free_model(model);
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
	model->n_cmd = -1;
	model->env = global_envp = ft_array_join(environ, NULL);
	clear_terminal();
	while (1)
	{
		print_prompt();
		str = readline("$ ");
		parser(str, model, model->env);
		ret = check_exit(model);
		if (ret >= 0)
			return (ret);
		else
			execute(model);
	}
	clear_history();
	return (0);
}
