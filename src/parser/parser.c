/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:27:33 by anramire          #+#    #+#             */
/*   Updated: 2022/09/23 09:17:25 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_substr_modified(char *str, int pos)
{
	char	*str_aux;
	int		len;
	int		i;

	i = pos;
	len = 0;
	if (str[pos] == '\0' || str[pos - 1] == '\0')
		return (NULL);
	while (str[pos] != '\0')
	{
		len++;
		pos++;
	}
	str_aux = (char *)malloc((len + 1) * sizeof(char));
	if (str_aux == NULL)
		return (NULL);
	pos = 0;
	while (str[i] != '\0')
	{
		str_aux[pos] = str[i];
		pos++;
		i++;
	}
	str_aux[pos] = '\0';
	free(str);
	return (str_aux);
}

static char	*get_command(char *str, t_cmd **new_command, int *err)
{
	int		i;
	int		command_found;
	int		num_argument;
	int		arg_found;
	int		pos;
	char	*str_aux;
	char	*new_str;

	i = 0;
	command_found = 0;
	num_argument = -1;
	arg_found = 0;
	//hola
	int ht_number; //Higher than number
	init_command(new_command);
	str_aux = clean_white_spaces(str);
	if ((str_aux[0] == ';') || (str_aux[0] == '|'))
		str_aux = clean_white_spaces(str);
	while (str_aux[i] != '\0')
	{
		//Checks output
		if (str_aux[i] == '>')
		{
			ht_number = 0;
			while (str_aux[i] == '>')
			{
				ht_number++;
				i++;
			}
			while (str_aux[i] == ' ')
				i++;
			if (!((str_aux[i] >= 'a') && (str_aux[i] <= 'z')) && !((str_aux[i] >= 'A') && (str_aux[i] <= 'Z')) && !((str_aux[i] >= '0') && str_aux[i] <= '9') && str_aux[i] != '\\')
			{
				ft_printf("char: %c\n", str_aux[i]);
				(*err) = -1;
				return (NULL);
			}
			if (ht_number == 1)
			{
				i = get_output_file(*new_command, str_aux, i);
				continue ;
			}
			else if (ht_number == 2)
			{
				i = get_double_file(*new_command, str_aux, i);
				continue ;
			}
			else
			{
				*err = -1;
				return (NULL);
			}
		}
		//Checks input
		if (str_aux[i] == '<')
		{
			ht_number = 0;
			while (str_aux[i] == '<')
			{
				ht_number++;
				i++;
			}
			while (str_aux[i] == ' ')
				i++;
			if (!((str_aux[i] >= 'a') && (str_aux[i] <= 'z')) && !((str_aux[i] >= 'A') && (str_aux[i] <= 'Z')) && !((str_aux[i] >= '0') && str_aux[i] <= '9') && str_aux[i] != '\\')
			{
				ft_printf("char: %c\n", str_aux[i]);
				(*err) = -1;
				return (NULL);
			}
			if (ht_number == 1)
			{
				i = get_input_file(*new_command, str_aux, i);
				continue ;
			}
			else if (ht_number == 2)
			{
				i = get_heredocs(*new_command, str_aux, i);
				continue ;
			}
			else
			{
				*err = -1;
				return (NULL);
			}
		}
		//-------------------
		if (str_aux[i] == '|')
		{
			(*new_command)->pipe = 1;
			break ;
		}
		if (str_aux[i] == ';')
			break ;
		if (str_aux[i] == '"')
		{
			(*err) = get_arguments_with_quotes(*new_command, str_aux, &i,
					&num_argument);
			if (*err != 0)
				return (NULL);
			continue ;
		}
		if (str_aux[i] == '\'')
		{
			(*err) = get_arguments_with_simp_quotes(*new_command, str_aux, &i,
					&num_argument);
			if (*err != 0)
				return (NULL);
			continue ;
		}
		if (str_aux[i] != ' ' && (str_aux[i] != '\0'))
		{
			if (arg_found == 0)
			{
				num_argument++;
				(*new_command)->args[num_argument] = (char *)malloc(sizeof(char));
				(*new_command)->args[num_argument][0] = '\0';
				arg_found = 1;
			}
			(*new_command)->args[num_argument] = ft_concat_char((*new_command)->args[num_argument],
																str_aux[i]);
		}
		else
		{
			if (arg_found != 0)
			{
				arg_found = 0;
			}
		}
		i++;
	}
	pos = i + 1;
	(*new_command)->args[num_argument + 1] = NULL;
	new_str = ft_substr_modified(str_aux, pos);
	return (new_str);
}

void	parser(char *str, t_model *model, char **envp)
{
	char	*str_aux;
	int		error;

	// int i;
	error = 0;
	add_history(str);
	model->n_cmd = 0;
	model->cmds = (t_cmd **)malloc(100 * sizeof(t_cmd *));
	str_aux = get_command(str, (&model->cmds[model->n_cmd]), &error);
	if (error == -1)
	{
		ft_printf("Error: Bad command syntax!!!\n");
		model = NULL;
		return ;
	}
	else if (error == -2)
	{
		ft_printf("Error: Quotes not closed!!!\n");
		model = NULL;
		return ;
	}
	model->n_cmd++;
	while (str_aux)
	{
		str_aux = get_command(str_aux, &(model->cmds[model->n_cmd]), &error);
		if (error == -1)
		{
			ft_printf("Error: Bad command syntax!!!\n");
			model = NULL;
			return ;
		}
		else if (error == -2)
		{
			ft_printf("Error: Quotes not closed!!!\n");
			model = NULL;
			return ;
		}
		model->n_cmd++;
	}
	check_expansions(model, envp);
	show_list(model);
}