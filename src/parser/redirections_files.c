/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:55:51 by anramire          #+#    #+#             */
/*   Updated: 2022/09/23 19:48:52 by anramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		checks_output(t_cmd **new_command, char *str_aux, int *i, int *err)
{
	int ht_number;

	if (str_aux[*i] == '>')
	{
		ht_number = 0;
		while (str_aux[*i] == '>')
		{
			ht_number++;
			(*i)++;
		}
		while (str_aux[*i] == ' ')
			i++;
		if (!((str_aux[*i] >= 'a') && (str_aux[*i] <= 'z')) && !((str_aux[*i] >= 'A') && (str_aux[*i] <= 'Z')) && !((str_aux[*i] >= '0') && str_aux[*i] <= '9') && str_aux[*i] != '\\')
		{
			ft_printf("char: %c\n", str_aux[*i]);
			(*err) = -1;
			return 1;
		}
		if (ht_number == 1)
		{
			(*i) = get_output_file(*new_command, str_aux, *i);
			return 0;
		}
		else if (ht_number == 2)
		{
			(*i) = get_double_file(*new_command, str_aux, *i);
			return 0;
		}
		else
		{
			*err = -1;
			return 1;
		}
	}
	return 2;
}

int		checks_input(t_cmd **new_command, char *str_aux, int *i, int *err)
{
	int	lt_number;

	if (str_aux[*i] == '<')
	{
		lt_number = 0;
		while (str_aux[*i] == '<')
		{
			lt_number++;
			(*i)++;
		}
		while (str_aux[*i] == ' ')
			(*i)++;
		if (!((str_aux[*i] >= 'a') && (str_aux[*i] <= 'z')) && !((str_aux[*i] >= 'A') && (str_aux[*i] <= 'Z')) && !((str_aux[*i] >= '0') && str_aux[*i] <= '9') && str_aux[*i] != '\\')
		{
			ft_printf("char: %c\n", str_aux[*i]);
			(*err) = -1;
			return -1;
		}
		if (lt_number == 1)
		{
			(*i) = get_input_file(*new_command, str_aux, *i);
			return 0;
		}
		else if (lt_number == 2)
		{
			(*i) = get_heredocs(*new_command, str_aux, *i);
			return 0;
		}
		else
		{
			*err = -1;
			return -1;
		}
	}
	return 2;
}

