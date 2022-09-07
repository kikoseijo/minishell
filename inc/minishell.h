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

#endif
