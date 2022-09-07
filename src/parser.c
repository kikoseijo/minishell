/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 08:47:12 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/07 11:02:03 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
** Command Parser
*/

static void run_parser(char **envp)
{
	int i;

	i = 0;
	while (envp[i]) {
		printf("%s\n", envp[i]);
		i++;
	}
}

int parser(int argc, char **argv, char **envp)
{
	if(argc < 2 || !argv)
		return (-1);
	run_parser(envp);
	return (0);
}
