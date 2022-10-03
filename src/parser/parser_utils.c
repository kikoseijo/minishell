/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 10:34:24 by anramire          #+#    #+#             */
/*   Updated: 2022/10/03 20:58:01 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f');
}

char	*clean_white_spaces(char *str)
{
	char	*str_aux;
	int		end;
	int		pos;
	int		i;

	pos = 0;
	while (is_space(str[pos]))
		pos++;
	end = pos;
	while (str[end] != '\0')
		end++;
	str_aux = (char *)ft_calloc((end - pos + 1), sizeof(char));
	if (str_aux == NULL)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (pos < end)
	{
		str_aux[i] = str[pos];
		pos++;
		i++;
	}
	free(str);
	return (str_aux);
}

int	get_arguments_with_quotes(t_cmd *command, char *str, int *pos,
		int *num_argument)
{
	int	error;
	int	quotes_found;

	quotes_found = 0;
	error = 0;
	(*num_argument)++;
	(*pos)++;
	command->args[*num_argument] = (char *)ft_calloc(1, sizeof(char));
	// command->args[*num_argument][0] = '\0';
	while (str[*pos] != '\0' && str[*pos] != '\"')
	{
		if (str[*pos] == '\\')
		{
			if (str[*pos + 1] == '\"')
			{
				*pos += 1;
				command->args[*num_argument] = ft_concat_char(command->args[*num_argument],
																str[*pos]);
				*pos += 1;
				continue ;
			}
		}
		command->args[*num_argument] = ft_concat_char(command->args[*num_argument],
														str[*pos]);
		(*pos) += 1;
		if (str[*pos] == '\"')
			quotes_found = 1;
	}
	command->scape_arguments[*num_argument] = 0;
	if (str[*pos] == '\"')
		quotes_found = 1;
	(*pos) += 1;
	if (quotes_found == 0)
		error = -2;
	return (error);
}

//Function to show list of cmds

void	show_list(t_model *command_line)
{
	int	i;
	int	n;

	ft_printf("N. pipes: %d\n", command_line->n_cmd);
	n = 0;
	while (n < (command_line->n_cmd))
	{
		i = 0;
		ft_printf("<------------------------->\n");
		while (command_line->cmds[n]->args[i] != NULL)
		{
			ft_printf("args[%d]: %s\n", i, command_line->cmds[n]->args[i]);
			i++;
		}
		i = 0;
		while (i < command_line->cmds[n]->n_fdout)
		{
			ft_printf("simple output file[%d]: %s\n", i,
					command_line->cmds[n]->fd_out[i]);
			i++;
		}
		i = 0;
		while (i < command_line->cmds[n]->num_double_out)
		{
			ft_printf("double output file[%d]: %s\n", i,
					command_line->cmds[n]->fd_double_out[i]);
			i++;
		}
		i = 0;
		while (i < command_line->cmds[n]->num_simple_in)
		{
			ft_printf("simple input file[%d]: %s\n", i,
					command_line->cmds[n]->fd_simple_in[i]);
			i++;
		}
		i = 0;
		while (i < command_line->cmds[n]->num_heredocs)
		{
			ft_printf("heredocs[%d]: %s\n", i,
					command_line->cmds[n]->heredocs_close[i]);
			i++;
		}
		ft_printf("pipe: %d\n", command_line->cmds[n]->pipe);
		n++;
	}
	ft_printf("final\n");
}

void	init_command(t_cmd **new_command)
{
	int	i;

	i = 0;
	*new_command = (t_cmd *)malloc(sizeof(t_cmd));
	(*new_command)->args = (char **)ft_calloc(200, sizeof(char *));
	(*new_command)->expansions = (int *)ft_calloc(200, sizeof(int));
	(*new_command)->scape_arguments = (int *)ft_calloc(200, sizeof(int));
	while (i < 200)
	{
		(*new_command)->expansions[i] = 1;
		(*new_command)->scape_arguments[i] = 1;
		i++;
	}
	(*new_command)->num_args = -1;
	(*new_command)->pipe = 0;
	(*new_command)->fd_out = (char **)ft_calloc(100, sizeof(char *));
	(*new_command)->n_fdout = 0;
	(*new_command)->fd_double_out = (char **)ft_calloc(100, sizeof(char *));
	(*new_command)->num_double_out = 0;
	(*new_command)->fd_simple_in = (char **)ft_calloc(100, sizeof(char *));
	(*new_command)->num_simple_in = 0;
	(*new_command)->heredocs_close = (char **)ft_calloc(100, sizeof(char *));
	(*new_command)->num_heredocs = 0;
}

int	get_output_file(t_cmd *c, char *str, int pos)
{
	int	end;
	int	i;

	//char	*file; Unused
	end = pos;
	while (str[end] != '\0' && (str[end] != ' ') && (str[end] != '|') && (str[end] != ';') && (str[end] != '>'))
		end++;
	c->fd_out[c->n_fdout] = (char *)ft_calloc((end - pos + 1), sizeof(char));
	if (c->fd_out[c->n_fdout] == NULL)
		return (-1);
	i = 0;
	while (str[pos] != '\0' && (str[pos] != ' ') && (str[pos] != '|') && (str[pos] != ';') && (str[pos] != '>'))
	{
		c->fd_out[c->n_fdout][i] = str[pos];
		pos++;
		i++;
	}
	(c->n_fdout)++;
	return (end);
}

int	get_double_file(t_cmd *command, char *str, int pos)
{
	int	end;
	int	i;

	//char *file; Unused
	end = pos;
	while (str[end] != '\0' && (str[end] != ' ') && (str[end] != '|') && (str[end] != ';') && (str[end] != '>'))
		end++;
	command->fd_double_out[command->num_double_out] = (char *)ft_calloc((end
				- pos + 1), sizeof(char));
	if (command->fd_double_out[command->num_double_out] == NULL)
		return (-1);
	i = 0;
	while (str[pos] != '\0' && (str[pos] != ' ') && (str[pos] != '|') && (str[pos] != ';') && (str[pos] != '>'))
	{
		command->fd_double_out[command->num_double_out][i] = str[pos];
		pos++;
		i++;
	}
	(command->num_double_out)++;
	return (end);
}
