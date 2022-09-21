/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 08:57:42 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/21 20:34:28 by anramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
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
	size_t		num_args;
	char		**fd_simple_in;
	size_t		num_simple_in;
	char		**fd_out;
	size_t		n_fdout;
	char		**fd_double_out;
	size_t		num_double_out;
	char		**heredocs_close;
	size_t		num_heredocs;
	int			pipe;
	char		*error;
}				t_cmd;

typedef struct s_model
{
	t_cmd		**cmds;
	int			n_cmd;
	int			background;
	const char	*infile;
	char		**env_paths;
}				t_model;

void			parser(char *str, t_model *model, char **envp);
void			execute(t_model *model, char **envp);
void			free_model(t_model *model);

// env.c
char			*get_env_value(char *key, char **envp);
void			set_env_value(char *key, char *value, char **envp);

// built_in.c
int				ft_exit(t_model *model);
int				ft_cd(char *path, char **envp);

//Utilities functions
char			*clean_white_spaces(char *str);
int	get_arguments_with_quotes(t_cmd *command,
								char *str,
								int *pos,
								int *num_argument);

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

#endif
