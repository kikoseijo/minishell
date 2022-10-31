/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:20:55 by anramire          #+#    #+#             */
/*   Updated: 2022/10/31 20:08:45 by cmac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	get_expansion(char **str, char **enviroment, int scape)
{
	int		i;
	char	*tmp;

	tmp = (char *)ft_calloc(1, sizeof(char));
	i = 0;
	while (tmp[i] && tmp[i] != '\0')
	{
		if (check_scapes(str, tmp, &i, scape) == 1)
			continue ;
		if (tmp[i] == '$')
		{
			main_loop(tmp, &i, enviroment, str);
			continue ;
		}
		*str = ft_concat_char(*str, tmp[i]);
		i++;
	}
	free(tmp);
}

int	get_input_file(t_cmd *command, char *str, int pos)
{
	int	end;
	int	i;

	end = pos;
	while (str[end] != '\0' && (str[end] != ' ') && (str[end] != '|')
		&& (str[end] != ';') && (str[end] != '<'))
		end++;
	if (command->infile != NULL)
		free(command->infile);
	command->infile = (char *)ft_calloc((end - pos + 1), sizeof(char));
	if (command->infile == NULL)
		return (-1);
	i = 0;
	while (str[pos] != '\0' && (str[pos] != ' ') && (str[pos] != '|')
		&& (str[pos] != ';') && (str[pos] != '<'))
	{
		command->infile[i] = str[pos];
		pos++;
		i++;
	}
	return (end);
}

int	get_heredocs(t_cmd *command, char *str, int pos)
{
	int	end;
	int	i;

	end = pos;
	while (str[end] != '\0' && (str[end] != ' ') && (str[end] != '|')
		&& (str[end] != ';') && (str[end] != '<'))
		end++;
	command->heredocs_close[command->num_heredocs] = (char *)ft_calloc(end - pos
			+ 1, sizeof(char));
	if (command->heredocs_close[command->num_heredocs] == NULL)
		return (-1);
	i = 0;
	while (str[pos] != '\0' && (str[pos] != ' ') && (str[pos] != '|')
		&& (str[pos] != ';') && (str[pos] != '<'))
	{
		command->heredocs_close[command->num_heredocs][i] = str[pos];
		pos++;
		i++;
	}
	(command->num_heredocs)++;
	return (end);
}

void	check_expansions(t_model *model, char **enviroment)
{
	int	n;
	int	i;

	n = 0;
	while (n < model->n_cmd)
	{
		i = 1;
		while (model->cmds[n]->args[i] != NULL)
		{
			if (model->cmds[n]->expansions[i] != 0)
			{
				get_expansion(&(model->cmds[n]->args[i]), enviroment,
						model->cmds[n]->scape_arguments[i]);
			}
			i++;
		}
		n++;
	}
}

int	get_arguments_with_simp_quotes(t_cmd *command, char *str, int *pos,
		int *num_argument)
{
	int	error;
	int	returned_quotes;

	returned_quotes = 0;
	error = 0;
	(*num_argument)++;
	(*pos)++;
	command->args[*num_argument] = (char *)ft_calloc(1, sizeof(char));
	returned_quotes = simp_quotes_core(command, str, pos, num_argument);
	(command)->expansions[*num_argument] = 0;
	(*pos) += 1;
	if (returned_quotes < 0)
		error = -2;
	return (error);
}
