/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 08:57:42 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/07 11:02:28 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>

struct s_command {
		// Available space for arguments currently preallocated
		int _numberOfAvailableArguments;
		// Number of arguments
		int _numberOfArguments;
		// Array of arguments
		char ** _arguments;
		// SimpleCommand();
		// void insertArgument(char *argument);
} t_command;

int parser(int argc, char **argv, char **envp);

#endif
