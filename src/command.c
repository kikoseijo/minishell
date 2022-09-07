/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:53:59 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/07 16:47:21 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
** SimpleCommand/s
*/



void simple_command()
{
	// constructs a simple empty command
}

/*
** 	inserts a new argument into the simple_command and enlarges
** 	the _arguments array if necessary.
** 	It also makes sure that the last element is NULL
** 	since that is required for the exec() system call.
*/
void insert_argument(char *argument)
{
	printf("insert_argument(): %s\n", argument);
}

/*
** Command processor
*/

void prompt()
{

}

void print()
{

}

void execute(t_command *cmd)
{
	int ret;
	for ( int i = 0; i < cmd->_numberOfSimpleCommands; i++ )
	{
		ret = fork();
		if (ret == 0) {
			//child
			execvp(sCom[i]­>_args[0], sCom[i]­>_args);
			perror(“execvp”);
			_exit(1);
		}
		else if (ret < 0)
		{
			perror(“fork”);
			return;
		}
		// Parent shell continue
	} // for
	if (!background)
	{
		// wait for last process
		waitpid(ret, NULL);
	}
}

void clear()
{

}

/*
** The constructor C​ommand::Command(​) constructs and empty command that will
** be populated with the method
** Command::i​nsertSimpleCommand(SimpleCommand* simpleCommand).​insertSimpleCommand
** also enlarges the array _simpleCommands if necessary.
** The variables _outFile, _inputFile, _errFile will be NULL if
** no redirection was done, or the name of the file they are being redirected
**< to.
*/

void command()
{

}

void insert_simple_command( t_simple_command *simpleCommand )
{

}
