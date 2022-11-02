/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:27:33 by anramire          #+#    #+#             */
/*   Updated: 2022/11/02 21:13:53 by anramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	check_command(t_cmd **new_command, char *str_aux, int *i);
static int	core_parser(t_cmd **new_command, char *str_aux, int *i, int *err);

static char	*ft_substr_modified(char *str, int pos)
{
	char	*str_aux;
	int		len;
	int		i;

	i = pos + 1;
	len = 0;
	if (str[pos] == '\0' || (pos > 0 && str[pos - 1] == '\0'))
	{
		free(str);
		return (NULL);
	}
	while (str[pos] != '\0')
		pos++;
	len += (pos - i);
	allocate_memory(&str_aux, len + 1);
	pos = 0;
	while (str[i] != '\0')
	{
		str_aux[pos] = str[i];
		pos++;
		i++;
	}
	free(str);
	return (str_aux);
}

static char	*get_command(char *str, t_cmd **new_command, int *err)
{
	int		i;
	int		arg_found;
	char	*str_aux;
	char	*new_str;

	i = 0;
	arg_found = 0;
	init_command(new_command);
	str_aux = clean_white_spaces(str);
	free(str);
	if (core_parser(new_command, str_aux, &i, err) < 0)
	{
		free(str_aux);
		return (NULL);
	}
	(*new_command)->args[(*new_command)->num_args + 1] = NULL;
	new_str = ft_substr_modified(str_aux, i);
	return (new_str);
}

void	parser(char *str, t_model *model)
{
	char	*str_aux;
	int		error;

	if (!str)
		return ;
	error = 0;
	add_history(str);
	model->n_cmd = 0;
	model->cmds = (t_cmd **)malloc(100 * sizeof(t_cmd *));
	str_aux = get_command(str, &model->cmds[0], &error);
	if (check_error(error) != 0)
		return ;
	model->n_cmd++;
	while (str_aux)
	{
		str_aux = get_command(str_aux, &(model->cmds[model->n_cmd]), &error);
		if (check_error(error) != 0)
			return ;
		model->n_cmd++;
	}
	check_expansions(model);
}

/*
** show_list(model);
*/

static void	check_command(t_cmd **new_command, char *str_aux, int *i)
{
	if (str_aux[*i] != ' ' && (str_aux[*i] != '\0'))
	{
		if ((*new_command)->arg_found == 0)
		{
			(*new_command)->num_args += 1;
			(*new_command)->args[(*new_command)->num_args]
				= (char *)malloc(sizeof(char));
			(*new_command)->args[(*new_command)->num_args][0] = '\0';
			(*new_command)->arg_found = 1;
		}
		(*new_command)->args[(*new_command)->num_args]
			= ft_concat_char((*new_command)->args[(*new_command)->num_args],
				str_aux[*i]);
	}
	else
	{
		if ((*new_command)->arg_found != 0)
			(*new_command)->arg_found = 0;
	}
}

static int	core_parser(t_cmd **new_command, char *str_aux, int *i, int *err)
{
	while (str_aux[*i] != '\0')
	{
		if (checks_output(new_command, str_aux, i, err) == 0)
			continue ;
		else if (checks_output(new_command, str_aux, i, err) == -1)
			return (-1);
		if (checks_input(new_command, str_aux, i, err) == 0)
			continue ;
		else if (checks_input(new_command, str_aux, i, err) == -1)
			return (-1);
		if (str_aux[*i] == '|')
		{
			(*new_command)->pipe = 1;
			break ;
		}
		if (str_aux[*i] == ';')
			break ;
		if (check_quotes(new_command, str_aux, i, err) == 0)
			continue ;
		else if (check_quotes(new_command, str_aux, i, err) == -1)
			return (-1);
		check_command(new_command, str_aux, i);
		(*i)++;
	}
	return (0);
}
