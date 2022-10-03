/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:20:55 by anramire          #+#    #+#             */
/*   Updated: 2022/10/03 21:07:57 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	get_expansion(char **str, char **enviroment, int scape);

int	get_input_file(t_cmd *command, char *str, int pos)
{
	int	end;
	int	i;

	//char	*file; Unused
	end = pos;
	while (str[end] != '\0' && (str[end] != ' ') && (str[end] != '|') && (str[end] != ';') && (str[end] != '<'))
		end++;
	command->fd_simple_in[command->num_simple_in] = (char *)ft_calloc((end - pos
				+ 1), sizeof(char));
	if (command->fd_simple_in[command->num_simple_in] == NULL)
		return (-1);
	i = 0;
	while (str[pos] != '\0' && (str[pos] != ' ') && (str[pos] != '|') && (str[pos] != ';') && (str[pos] != '<'))
	{
		command->fd_simple_in[command->num_simple_in][i] = str[pos];
		pos++;
		i++;
	}
	command->num_simple_in++;
	return (end);
}

int	get_heredocs(t_cmd *command, char *str, int pos)
{
	int	end;
	int	i;

	//char	*file; Unused
	end = pos;
	while (str[end] != '\0' && (str[end] != ' ') && (str[end] != '|') && (str[end] != ';') && (str[end] != '<'))
		end++;
	command->heredocs_close[command->num_heredocs] = (char *)ft_calloc((end
				- pos + 1), sizeof(char));
	if (command->heredocs_close[command->num_heredocs] == NULL)
		return (-1);
	i = 0;
	while (str[pos] != '\0' && (str[pos] != ' ') && (str[pos] != '|') && (str[pos] != ';') && (str[pos] != '<'))
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

static void	get_expansion(char **str, char **enviroment, int scape)
{
	int		i;
	int		init;
	char	*aux;
	int		j;
	char	*copy_str;
	char	*env2;

	copy_str = *str;
	*str = (char *)ft_calloc(1, sizeof(char));
	i = 0;
	while (copy_str[i] != '\0')
	{
		if (copy_str[i] == '\\' && scape == 1)
		{
			i++;
			*str = ft_concat_char(*str, copy_str[i]);
			i++;
			continue ;
		}
		if (copy_str[i] == '$')
		{
			i++;
			init = i;
			while (copy_str[i] != ' ' && copy_str[i] != '$' && copy_str[i] != '\0')
				i++;
			aux = ft_substr(copy_str, init, i - init + 1);
			ft_printf("substr: %s\n", aux);
			j = 0;
			while (enviroment[j])
			{
				if (ft_strncmp(aux, enviroment[j], i - init) == 0)
				{
					free(aux);
					aux = *str;
					env2 = ft_substr(enviroment[j], i - init + 1,
							ft_strlen(enviroment[j]));
					ft_printf("prueba==> %s: %s\n", aux, env2);
					free(aux);
					*str = ft_strjoin(*str, env2);
					free(env2);
					break ;
				}
				j++;
			}
			continue ;
		}
		*str = ft_concat_char(*str, copy_str[i]);
		i++;
	}
	copy_str[i] = '\0';
	free(copy_str);
}

int	get_arguments_with_simp_quotes(t_cmd *command, char *str, int *pos,
		int *num_argument)
{
	int	error;
	int	quotes_found;

	quotes_found = 0;
	error = 0;
	(*num_argument)++;
	(*pos)++;
	command->args[*num_argument] = (char *)ft_calloc(1, sizeof(char));
	// command->args[*num_argument][0] = '\0';
	while (str[*pos] != '\0' && str[*pos] != '\'')
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
		if (str[*pos] == '\'')
			quotes_found = 1;
	}
	(command)->expansions[*num_argument] = 0;
	(*pos) += 1;
	if (quotes_found == 0)
		error = -2;
	return (error);
}
