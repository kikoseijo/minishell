/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 08:57:42 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/07 11:23:47 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
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
#include "../libft/inc/libft.h"

typedef struct s_simple_command {
	char *command;
	char **args;//terminated null
	size_t	num_args;//without null
	char **fd_simple_in;//input
	char **fd_simple_out;//output
	char **fd_doble_out;//double output
	char *heredoc_close; //heredoc
	int	pipe; //True or false
	char *error;
}t_simple_command;


typedef struct s_model{
	t_simple_command **commands;
	int num_commands;
}model;
void	parser_command(char *str);

//Utilities functions


char *clean_white_spaces(char *str);
int get_arguments_with_quotes(t_simple_command *command, char *str, int pos, int *num_argument);

#endif
