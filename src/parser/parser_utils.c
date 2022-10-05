/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 10:34:24 by anramire          #+#    #+#             */
/*   Updated: 2022/10/05 22:27:58 by anramire         ###   ########.fr       */
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
	while (str[pos] == ' ')
		pos++;
	end = pos;
	while (str[end] != '\0')
		end++;
	str_aux = (char *)malloc((end - pos + 1) * sizeof(char));
	if (str_aux == NULL)
		return (NULL);
	i = 0;
	while (pos < end)
	{
		str_aux[i] = str[pos];
		pos++;
		i++;
	}
	free(str);
	str_aux[i] = '\0';
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
	command->args[*num_argument] = (char *)malloc(sizeof(char));
	command->args[*num_argument][0] = '\0';
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
		ft_printf("output file: %s\n",
				command_line->cmds[n]->outfile);
		ft_printf("is_double_outfile: %d\n", command_line->cmds[n]->is_double_outfile);
		ft_printf("input file: %s\n",
					command_line->cmds[n]->infile);
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
	(*new_command)->args = (char **)malloc(200 * sizeof(char *));
	(*new_command)->expansions = (int *)malloc(200 * sizeof(int));
	(*new_command)->scape_arguments = (int *)malloc(200 * sizeof(int));
	while (i < 200)
	{
		(*new_command)->expansions[i] = 1;
		(*new_command)->scape_arguments[i] = 1;
		i++;
	}
	(*new_command)->num_args = -1;
	(*new_command)->pipe = 0;
	(*new_command)->is_double_outfile = -1;
	(*new_command)->outfile = NULL;
	(*new_command)->infile = NULL;
	//(*new_command)- = (char **)malloc(100 * sizeof(char *));
	//(*new_command)->n_fdout = 0;
	//(*new_command)->fd_double_out = (char **)malloc(100 * sizeof(char *));
	//(*new_command)->num_double_out = 0;
	//(*new_command)->fd_simple_in = (char **)malloc(100 * sizeof(char *));
	//(*new_command)->num_simple_in = 0;
	(*new_command)->heredocs_close = (char **)malloc(100 * sizeof(char *));
	(*new_command)->num_heredocs = 0;
}

int	get_output_file(t_cmd *command, char *str, int pos)
{
	int	end;
	int	i;

	end = pos;
	while (str[end] != '\0' && (str[end] != ' ') && (str[end] != '|') && (str[end] != ';') && (str[end] != '>'))
		end++;
	if(command->outfile != NULL)
		free(command->outfile);
	command->outfile = (char *)malloc((end - pos + 1)
			* sizeof(char));
	if (command->outfile == NULL)
		return (-1);
	i = 0;
	while (str[pos] != '\0' && (str[pos] != ' ') && (str[pos] != '|') && (str[pos] != ';') && (str[pos] != '>'))
	{
		command->outfile[i] = str[pos];
		pos++;
		i++;
	}
	command->outfile[i] = '\0';
	//(command->n_fdout)++;
	//ft_printf("end: %s\n", &str[end]);
	command->is_double_outfile = 0;
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
	if(command->outfile != NULL)
		free(command->outfile);
	command->outfile = (char *)malloc((end - pos + 1) * sizeof(char));
	if (command->outfile == NULL)
		return (-1);
	i = 0;
	while (str[pos] != '\0' && (str[pos] != ' ') && (str[pos] != '|') && (str[pos] != ';') && (str[pos] != '>'))
	{
		command->outfile[i] = str[pos];
		pos++;
		i++;
	}
	command->outfile[i] = '\0';
	command->is_double_outfile = 1;
	return (end);
}
