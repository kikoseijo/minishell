/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 08:57:42 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/16 07:44:11 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

/*----------- Old part -------------------------------------------
typedef struct s_simple_command {
		// Available space for arguments currently preallocated
		int _numberOfAvailableArguments;
		// Number of arguments
		int _numberOfArguments;
		// Array of arguments
		char ** _arguments;
} t_simple_command;

typedef struct s_command {
	int _numberOfAvailableSimpleCommands;
	int _numberOfSimpleCommands;
	t_simple_command **_simpleCommands;
	char *_outFile;
	char *_inputFile;
	char *_errFile;
	int _background;

	struct s_command *_currentCommand;
	t_simple_command *_currentSimpleCommand;
} t_command;

int parser(int argc, char **argv, char **envp);
-------------------------------------------------------------------*/
//
//--------------------------- New Part ------------------------------

#define MINISHELL_H
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

#include <sys/wait.h>
#include <fcntl.h>

#include "../libft/inc/libft.h"

typedef struct s_simple_command
{
	char *command;
	char **args; // terminated null
	size_t	num_args; // without null
	char **fd_simple_in; // input
	size_t num_simple_in;//Numbers of simple inputs
	char **fd_simple_out; // output
	size_t	num_simple_out; // Number of simple outputs
	char **fd_double_out; // double output
	size_t num_double_out; // Number of double outputs
	char *heredoc_close; // heredoc
	int	pipe; // True or false
	char *error;
} t_simple_command;


typedef struct s_model
{
	t_simple_command **commands;
	int num_commands;
	int background;
	const char* infile;
} t_model;

void	parser_command(char *str, t_model *model);

//Utilities functions


char *clean_white_spaces(char *str);
int get_arguments_with_quotes(t_simple_command *command, char *str, int pos, int *num_argument);
void	show_list(t_model *command_line);//Helper function to show list
void	init_command(t_simple_command **);//Function to init the simple_command
int	get_output_file(t_simple_command *command, char *str, int pos);//Insert simple output files
int	get_double_file(t_simple_command *command, char *str, int pos);//Insert double output files
int	get_input_file(t_simple_command *command, char *str, int pos);//Insert simple input files
int	get_heredocs(t_simple_command *command, char *str, int pos);

#endif
