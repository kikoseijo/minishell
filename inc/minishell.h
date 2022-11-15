/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 08:57:42 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/11/14 15:54:06 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <dirent.h>
# include <errno.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <fcntl.h>

# define ERROR_QUOTES -2
# define ERROR_SYNTAX -1

char		**g_envp;

typedef struct s_cmd
{
	char		**args;
	int			num_args;
	char		*infile;
	char		*outfile;
	int			is_double_outfile;
	char		**heredocs_close;
	int			num_heredocs;
	int			pipe;
	int			*expansions;
	int			*scape_arguments;
	int			arg_found;
}				t_cmd;

typedef struct s_model
{
	int			n_cmd;
	t_cmd		**cmds;
}				t_model;

typedef struct s_pipes
{
	int			tmpin;
	int			tmpout;
	int			fdin;
	int			fdout;
}				t_pipes;

void			parser(char *str, t_model *model);
int				execute(t_model *model);
int				exec_builtin(t_cmd *cmd);
char			*get_cmd(char *cmd);
void			free_model(t_model *model, int with_env);
void			kill_childs(int *childs, int i);
void			setup_fdout(t_model *m, int i, t_pipes *pipes);

// env.c
char			*get_env_value(char *key);
void			set_env_value(const char *key, char *value);
char			**get_env_path(void);
void			clear_terminal(void);
void			print_prompt(void);

// builtin
int				ft_cd(char *path);
void			ft_echo(int argc, char **args);
void			ft_env(void);
int				ft_exit(t_model *model);
void			ft_export(char *input);
void			ft_pwd(void);
void			ft_unset(char *input);

//Utilities functions
char			*clean_white_spaces(char *str);
int				get_arguments_with_quotes(t_cmd *cmd, char *str, int *pos,
					int *narg);

int				allocate_memory(char **str_aux, int tam);
//Parser functions
int				get_arguments_with_simp_quotes(t_cmd *command,
					char *str, int *pos, int *num_argument);
void			show_list(t_model *command_line);
void			init_command(t_cmd **new_command);
int				get_output_file(t_cmd *command, char *str, int pos);
int				get_double_file(t_cmd *command, char *str, int pos);
int				get_input_file(t_cmd *command, char *str, int pos);
int				get_heredocs(t_cmd *command, char *str, int pos);
void			check_expansions(t_model *model);
int				check_error(int error);
int				checks_output(t_cmd **new_command, char *str_aux, int *i,
					int *err);
int				checks_input(t_cmd **new_command, char *str_aux, int *i,
					int *err);
int				check_quotes(t_cmd **new_command, char *str_aux, int *i,
					int *err);
int				simp_quotes_core(t_cmd *command, char *str, int *pos,
					int *num_argument);
int				double_quotes_core(t_cmd *command, char *str, int *pos,
					int *num_argument);
void			main_loop(char *copy_str, int *i, char **str);
int				main_scapes(char *copy_str, int *i, char **str, int scape);

int				check_scapes(char **str, char *copy_str, int *i, int scape);
#endif
