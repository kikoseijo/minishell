/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:13:49 by anramire          #+#    #+#             */
/*   Updated: 2022/11/02 21:21:26 by anramire         ###   ########.fr       */
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

/*
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
*/

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

void	main_loop(char *copy_str, int *i, char **str)
{
	int		init;
	char	*aux;
	int		j;
	char	*env2;

	(*i)++;
	init = (*i);
	while (copy_str[*i] != ' ' && copy_str[*i] != '$' && copy_str[*i] != '\0')
		(*i)++;
	aux = ft_substr(copy_str, init, (*i) - init + 1);
	j = 0;
	while (g_envp[j])
	{
		if (ft_strncmp(aux, g_envp[j], (*i) - init) == 0)
		{
			free(aux);
			aux = *str;
			env2 = ft_substr(g_envp[j], (*i) - init + 1, ft_strlen(g_envp[j]));
			*str = ft_strjoin(*str, env2);
			free(aux);
			free(env2);
			break ;
		}
		j++;
	}
}
