/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:20:55 by anramire          #+#    #+#             */
/*   Updated: 2022/09/20 21:23:55 by anramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void get_expansion(char *str);

int	get_input_file(t_simple_command *command, char *str, int pos){
	int end;
	char *file;
	int i;
	end = pos;
	while(str[end] != '\0' && (str[end] != ' ') && (str[end] != '|') && (str[end] != ';') && (str[end] != '<'))
		end++;
	command->fd_simple_in[command->num_simple_in] = (char *)malloc((end - pos + 1) * sizeof(char));
	if(command->fd_simple_in[command->num_simple_in] == NULL)
		return -1;
	i = 0;
	while(str[pos] != '\0' && (str[pos] != ' ') && (str[pos] != '|') && (str[pos] != ';') && (str[pos] != '<'))
	{
		command->fd_simple_in[command->num_simple_in][i] = str[pos];
		pos++;
		i++;
	}
	command->fd_simple_in[command->num_simple_in][i] = '\0';
	(command->num_simple_in)++;
	return end;	
}


int	get_heredocs(t_simple_command *command, char *str, int pos){
	
	int end;
	char *file;
	int i;
	end = pos;
	while(str[end] != '\0' && (str[end] != ' ') && (str[end] != '|') && (str[end] != ';') && (str[end] != '<'))
		end++;
	command->heredocs_close[command->num_heredocs] = (char *)malloc((end - pos + 1) * sizeof(char));
	if(command->heredocs_close[command->num_heredocs] == NULL)
		return -1;
	i = 0;
	while(str[pos] != '\0' && (str[pos] != ' ') && (str[pos] != '|') && (str[pos] != ';') && (str[pos] != '<'))
	{
		command->heredocs_close[command->num_heredocs][i] = str[pos];
		pos++;
		i++;
	}
	command->heredocs_close[command->num_heredocs][i] = '\0';
	(command->num_heredocs)++;
	return end;
}


void check_expansions(t_model *model, char **enviroment)
{
	int n;
	int i;

	n = 0;
	while(n < model->num_commands)
	{
		i = 1;
		while(model->commands[n]->args[i] != NULL){
			get_expansion(model->commands[n]->args[i]);
			i++;
		}
		n++;
	}
}

static void get_expansion(char *str)
{
	int i;
	int init;
	char *aux;

	ft_printf("argumentos: %s\n", str);
	i = 0;
	while(str[i] != '\0'){
		if(str[i] == '$')
		{
			i++;
			init = i;
			while(str[i] != ' ' && str[i] != '$' && str[i] != '\0')
				i++;
			aux = ft_substr(str, init, i - init + 1);
			ft_printf("substr: %s\n", aux);
			continue;
		}
		i++;	
	}
}
