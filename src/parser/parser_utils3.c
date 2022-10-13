/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:13:49 by anramire          #+#    #+#             */
/*   Updated: 2022/10/10 19:01:03 by anramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		ft_printf("output file: %s\n", command_line->cmds[n]->outfile);
		ft_printf("is_double_outfile: %d\n",
			command_line->cmds[n]->is_double_outfile);
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
