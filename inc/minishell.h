/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 08:57:42 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/21 12:46:41 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_simple_command
{
	char				**args;
	size_t				num_args;
	char				**fd_simple_in;
	size_t				num_simple_in;
	char				**fd_out;
	size_t				n_fdout;
	char				**fd_double_out;
	size_t				num_double_out;
	char				**heredocs_close;
	size_t				num_heredocs;
	int					pipe;
	char				*error;
}						t_simple_command;

typedef struct s_model
{
	t_simple_command	**cmds;
	int					n_cmd;
	int					background;
	const char			*infile;
	char				**env_paths;
}						t_model;

void					parser(char *str, t_model *model, char **envp);
void					execute(t_model *model, char **envp);

//Utilities functions

char					*clean_white_spaces(char *str);
int	get_arguments_with_quotes(t_simple_command *command,
								char *str,
								int pos,
								int *num_argument);
void					show_list(t_model *command_line);
void					init_command(t_simple_command **new_command);
int						get_output_file(t_simple_command *command, char *str,
							int pos);
int						get_double_file(t_simple_command *command, char *str,
							int pos);
int						get_input_file(t_simple_command *command, char *str,
							int pos);
int						get_heredocs(t_simple_command *command, char *str,
							int pos);
void					check_expansions(t_model *model, char **enviroment);

#endif
