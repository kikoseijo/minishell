/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 08:57:42 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/28 22:11:58 by cmac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/wait.h>

# define ERROR_QUOTES -2
# define ERROR_SYNTAX -1

typedef struct s_cmd
{
	char		**args;
	int			num_args;
	char		**fd_simple_in;
	int			num_simple_in;
	char		**fd_out;
	int			n_fdout;
	char		**fd_double_out;
	int			num_double_out;
	char		**heredocs_close;
	int			num_heredocs;
	int			pipe;
	char		*error;
	int			*expansions;
	int			*scape_arguments;
}				t_cmd;

typedef struct s_model
{
	t_cmd		**cmds;
	int			n_cmd;
	char		***env;
	char		**env_paths;
	const char	*infile;
	const char	*infile_type;
	const char	*outfile;
	const char	*outfile_type;
}				t_model;

typedef struct s_pipes
{
	int			tmpin;
	int			tmpout;
	int			fdin;
	int			fdout;
}				t_pipes;

void			parser(char *str, t_model *model, char **envp);
int				execute(t_model *model, char **envp);
int				exec_builtin(t_cmd *cmd, char ***envp);
char			*get_cmd(char **paths, char *cmd);
void			free_model(t_model *model);
void			kill_childs(int *childs, int i, t_model *model);

// env.c
char			*get_env_value(char *key, char ***envp);
void			set_env_value(char *key, char *value, char ***envp);

// builtin
int				ft_cd(char *path, char ***envp);
void			ft_echo(int argc, char **args);
void			ft_env(char **envp);
int				ft_exit(t_model *model);
void			ft_export(char *input, char ***envp);
void			ft_pwd(void);
void			ft_unset(char *input, char ***envp);

//Utilities functions
char			*clean_white_spaces(char *str);
int				get_arguments_with_quotes(t_cmd *cmd, char *str, int *pos,
					int *narg);
//Parser functions
int	get_arguments_with_simp_quotes(t_cmd *command,
									char *str,
									int *pos,
									int *num_argument);
void			show_list(t_model *command_line);
void			init_command(t_cmd **new_command);
int				get_output_file(t_cmd *command, char *str, int pos);
int				get_double_file(t_cmd *command, char *str, int pos);
int				get_input_file(t_cmd *command, char *str, int pos);
int				get_heredocs(t_cmd *command, char *str, int pos);
void			check_expansions(t_model *model, char **enviroment);
int				check_error(int error, t_model *model);
int				checks_output(t_cmd **new_command, char *str_aux, int *i,
					int *err);
int				checks_input(t_cmd **new_command, char *str_aux, int *i,
					int *err);
int				check_quotes(t_cmd **new_command, char *str_aux, int *i,
					int *err);
#endif
