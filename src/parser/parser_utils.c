/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 10:34:24 by anramire          #+#    #+#             */
/*   Updated: 2022/11/02 21:05:51 by anramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*clean_white_spaces(char *str)
{
	char	*str_aux;
	int		end;
	int		pos;
	int		i;

	pos = 0;
	if (!str)
		return (str);
	while (str[pos] == ' ')
		pos++;
	end = pos;
	while (str[end] != '\0')
		end++;
	str_aux = (char *)ft_calloc(end - pos + 1, sizeof(char));
	if (str_aux == NULL)
		return (NULL);
	i = 0;
	while (pos < end)
	{
		str_aux[i] = str[pos];
		pos++;
		i++;
	}
	return (str_aux);
}

int	get_arguments_with_quotes(t_cmd *command, char *str, int *pos,
		int *num_argument)
{
	int	error;
	int	returned_quotes;

	returned_quotes = 0;
	error = 0;
	(*num_argument)++;
	(*pos)++;
	command->args[*num_argument] = (char *)malloc(sizeof(char));
	command->args[*num_argument][0] = '\0';
	returned_quotes = double_quotes_core(command, str, pos, num_argument);
	command->scape_arguments[*num_argument] = 0;
	(*pos) += 1;
	if (returned_quotes < 0)
		error = -2;
	return (error);
}

//Function to show list of cmds

void	init_command(t_cmd **new_command)
{
	int	i;

	i = 0;
	*new_command = (t_cmd *)malloc(sizeof(t_cmd));
	(*new_command)->args = (char **)ft_calloc(200, sizeof(char *));
	(*new_command)->expansions = (int *)malloc(200 * sizeof(int));
	(*new_command)->scape_arguments = (int *)malloc(200 * sizeof(int));
	while (i < 200)
	{
		(*new_command)->expansions[i] = 1;
		(*new_command)->scape_arguments[i] = 1;
		i++;
	}
	(*new_command)->arg_found = 0;
	(*new_command)->num_args = -1;
	(*new_command)->pipe = 0;
	(*new_command)->is_double_outfile = -1;
	(*new_command)->outfile = NULL;
	(*new_command)->infile = NULL;
	(*new_command)->num_heredocs = 0;
}

int	get_output_file(t_cmd *command, char *str, int pos)
{
	int	end;
	int	i;

	end = pos;
	while (str[end] != '\0' && (str[end] != ' ') && (str[end] != '|')
		&& (str[end] != ';') && (str[end] != '>'))
		end++;
	if (command->outfile != NULL)
		free(command->outfile);
	command->outfile = (char *)malloc((end - pos + 1) * sizeof(char));
	if (command->outfile == NULL)
		return (-1);
	i = 0;
	while (str[pos] != '\0' && (str[pos] != ' ') && (str[pos] != '|')
		&& (str[pos] != ';') && (str[pos] != '>'))
	{
		command->outfile[i] = str[pos];
		pos++;
		i++;
	}
	command->outfile[i] = '\0';
	command->is_double_outfile = 0;
	return (end);
}

int	get_double_file(t_cmd *command, char *str, int pos)
{
	int	end;
	int	i;

	end = pos;
	while (str[end] != '\0' && (str[end] != ' ') && (str[end] != '|')
		&& (str[end] != ';') && (str[end] != '>'))
		end++;
	if (command->outfile != NULL)
		free(command->outfile);
	command->outfile = (char *)malloc((end - pos + 1) * sizeof(char));
	if (command->outfile == NULL)
		return (-1);
	i = 0;
	while (str[pos] != '\0' && (str[pos] != ' ') && (str[pos] != '|')
		&& (str[pos] != ';') && (str[pos] != '>'))
	{
		command->outfile[i] = str[pos];
		pos++;
		i++;
	}
	command->outfile[i] = '\0';
	command->is_double_outfile = 1;
	return (end);
}
