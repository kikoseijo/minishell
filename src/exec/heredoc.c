/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:34:10 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/11/28 19:10:07 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	heredoc(t_cmd *cmd)
{
	int		fdpipe[2];
	char	*line;
	char	*close_doc;

	if (pipe(fdpipe) < 0)
		return (-1);
	line = readline("> ");
	close_doc = cmd->heredocs_close[cmd->num_heredocs - 1];
	while (ft_strcmp(close_doc, line) != 0)
	{
		ft_putstr_fd(line, fdpipe[1]);
		ft_putstr_fd((char *)"\n", fdpipe[1]);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(fdpipe[1]);
	return (fdpipe[0]);
}
