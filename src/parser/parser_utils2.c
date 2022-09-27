/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:20:55 by anramire          #+#    #+#             */
/*   Updated: 2022/09/27 22:56:09 by anramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	get_expansion(char **str, char **enviroment);

int	get_input_file(t_cmd *command, char *str, int pos)
{
	int		end;
	//char	*file; Unused
	int		i;

	end = pos;
	while (str[end] != '\0' && (str[end] != ' ') && (str[end] != '|') && (str[end] != ';') && (str[end] != '<'))
		end++;
	command->fd_simple_in[command->num_simple_in] = (char *)malloc((end - pos
				+ 1) * sizeof(char));
	if (command->fd_simple_in[command->num_simple_in] == NULL)
		return (-1);
	i = 0;
	while (str[pos] != '\0' && (str[pos] != ' ') && (str[pos] != '|') && (str[pos] != ';') && (str[pos] != '<'))
	{
		command->fd_simple_in[command->num_simple_in][i] = str[pos];
		pos++;
		i++;
	}
	command->fd_simple_in[command->num_simple_in][i] = '\0';
	(command->num_simple_in)++;
	return (end);
}

int	get_heredocs(t_cmd *command, char *str, int pos)
{
	int		end;
	//char	*file; Unused
	int		i;

	end = pos;
	while (str[end] != '\0' && (str[end] != ' ') && (str[end] != '|') && (str[end] != ';') && (str[end] != '<'))
		end++;
	command->heredocs_close[command->num_heredocs] = (char *)malloc((end - pos
				+ 1) * sizeof(char));
	if (command->heredocs_close[command->num_heredocs] == NULL)
		return (-1);
	i = 0;
	while (str[pos] != '\0' && (str[pos] != ' ') && (str[pos] != '|') && (str[pos] != ';') && (str[pos] != '<'))
	{
		command->heredocs_close[command->num_heredocs][i] = str[pos];
		pos++;
		i++;
	}
	command->heredocs_close[command->num_heredocs][i] = '\0';
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
			if(model->cmds[n]->expansions[i] != 0)
			{
				get_expansion(&(model->cmds[n]->args[i]), enviroment);
			}
			i++;
		}
		n++;
	}
}

static void	get_expansion(char **str, char **enviroment)
{
	int		i;
	int		init;
	char	*aux;
	int		j;
	char *copy_str;
	
	copy_str = *str;
	*str = (char *)malloc(sizeof(char));
	(*str)[0] = '\0';
	ft_printf("argumentos: %s\n", copy_str);
	i = 0;
	while (copy_str[i] != '\0')
	{
		if(copy_str[i] == '\\')
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
					char *env2 = ft_substr(enviroment[j], i - init + 1, ft_strlen(enviroment[j]));
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
	command->args[*num_argument] = (char *)malloc(sizeof(char));
	command->args[*num_argument][0] = '\0';
	while (str[*pos] != '\0' && str[*pos] != '\'')
	{
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
