/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:56:40 by anramire          #+#    #+#             */
/*   Updated: 2022/12/01 16:07:06 by jseijo-p         ###   ########.fr       */
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

int	check_scapes(char **str, char *copy_str, int *i, int scape)
{
	if (copy_str[*i] == '\\' && scape == 1)
	{
		(*i)++;
		*str = ft_concat_char(*str, copy_str[*i]);
		(*i)++;
		return (1);
	}
	return (0);
}

int	simp_quotes_core(t_cmd *c, char *str, int *pos, int *n_arg)
{
	int	quotes_found;

	quotes_found = 0;
	while (str[*pos] != '\0' && str[*pos] != '\'')
	{
		if (str[*pos] == '\\')
		{
			if (str[*pos + 1] == '\"')
			{
				*pos += 1;
				c->args[*n_arg] = ft_concat_char(c->args[*n_arg], str[*pos]);
				*pos += 1;
				continue ;
			}
		}
		c->args[*n_arg] = ft_concat_char(c->args[*n_arg], str[*pos]);
		(*pos) += 1;
		if (str[*pos] == '\'')
			quotes_found = 1;
	}
	if (str[*pos] == '\'')
		quotes_found = 1;
	if (quotes_found == 0)
		return (-1);
	return (1);
}

int	double_quotes_core(t_cmd *c, char *str, int *pos, int *n_arg)
{
	int	quotes_found;

	quotes_found = 0;
	while (str[*pos] != '\0' && str[*pos] != '\"')
	{
		if (str[*pos] == '\\')
		{
			if (str[*pos + 1] == '\"')
			{
				*pos += 1;
				c->args[*n_arg] = ft_concat_char(c->args[*n_arg], str[*pos]);
				*pos += 1;
				continue ;
			}
		}
		c->args[*n_arg] = ft_concat_char(c->args[*n_arg], str[*pos]);
		(*pos) += 1;
		if (str[*pos] == '\"')
			quotes_found = 1;
	}
	if (str[*pos] == '\"')
		quotes_found = 1;
	if (quotes_found == 0)
		return (-1);
	return (1);
}
