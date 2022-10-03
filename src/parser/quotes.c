/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:56:40 by anramire          #+#    #+#             */
/*   Updated: 2022/09/23 20:36:07 by anramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_quotes(t_cmd **new_command, char *str_aux, int *i, int *err)
{
	if (str_aux[*i] == '"')
	{
		(*err) = get_arguments_with_quotes(*new_command, str_aux, i,
				&(*new_command)->num_args);
		if (*err != 0)
			return (-1);
		return (0);
	}
	if (str_aux[*i] == '\'')
	{
		(*err) = get_arguments_with_simp_quotes(*new_command, str_aux, i,
				&(*new_command)->num_args);
		if (*err != 0)
			return (-1);
		return (0);
	}
	return (2);
}
