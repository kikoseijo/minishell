/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:27:33 by anramire          #+#    #+#             */
/*   Updated: 2022/07/05 21:35:46 by anramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *ft_substr_modified(char *str, int pos);
char	*get_command(char *str, t_simple_command **new_command);

void	parser_command(char *str) {
	model *command_line;
	char *str_aux;
	int i;
	int n;

	command_line = (model *)malloc(sizeof(model));
	command_line->num_commands = 0;
	command_line->commands = (t_simple_command **)malloc(100 * sizeof(t_simple_command *));
	str_aux = get_command(str, (&command_line->commands[command_line->num_commands]));
	command_line->num_commands++;
	while(str_aux)
	{
		str_aux = get_command(str_aux, &(command_line->commands[command_line->num_commands]));
		command_line->num_commands++;
	}
	
	n = 0;
	while(n < (command_line->num_commands)){
	i = 0;
		ft_printf("command: %s\n", command_line->commands[n]->command);
	while(command_line->commands[n]->args[i] != NULL){
			ft_printf("args[%d]: %s\n", i, command_line->commands[n]->args[i]);
			i++;
		}
		n++;
	}
}

char	*get_command(char *str, t_simple_command **new_command) 
{
	int i = 0;
	int command_found = 0;
	int num_argument = -1;
	int arg_found = 0;
	int pos;
	char *str_aux;

	*new_command = (t_simple_command *)malloc(sizeof(t_simple_command));
	(*new_command)->command = (char *)malloc(sizeof(char));
	(*new_command)->command[0] = '\0';
	(*new_command)->args = (char **)malloc(200 * sizeof(char *));
	(*new_command)->pipe = 0;
	str_aux = clean_white_spaces(str);
	
	while(str_aux[i] != '\0')
	{
		if(str_aux[i] == '|')
		{	
			(*new_command)->pipe = 1;
			break;
		}
		if(str_aux[i] == ';' && command_found == 1)
			break;
		if(str_aux[i] == '"')
		{
			i = get_arguments_with_quotes(*new_command, str_aux, i, &num_argument);
			continue;
		}

		if(str_aux[i] != ' ' && command_found == 0)
		{
			(*new_command)->command = ft_concat_char((*new_command)->command, str_aux[i]);
			i++;
			continue;
		}
		else {
			command_found = 1;
		}

		if(str_aux[i] != ' ' && (str_aux[i] != '\0'))
		{
			if(arg_found == 0){
				num_argument++;
				(*new_command)->args[num_argument] = (char *)malloc(sizeof(char));	
				(*new_command)->args[num_argument][0] = '\0';
				arg_found = 1;
			}
			(*new_command)->args[num_argument] = ft_concat_char((*new_command)->args[num_argument], str_aux[i]);
		}else {
			if(arg_found != 0)
			{
				arg_found = 0;
			}
		}
		
		i++;
	}
	pos = i + 1;
	
	(*new_command)->args[num_argument + 1] = NULL;


	/*	printf("command: %s\n",new_command->command);
		i = 0;
		while(new_command->args[i] != NULL){
			printf("args[%d]: %s\n",i, new_command->args[i]);
			i++;
		}*/
	return ft_substr_modified(str_aux, pos);
}

char *ft_substr_modified(char *str, int pos){
	
	char *str_aux;
	int len;
	int i;
	
	i = pos;
	len = 0;
	if(str[pos] == '\0')
		return NULL;
	while(str[pos] != '\0'){
		len++;
		pos++;
	}
	str_aux = (char *)malloc((len + 1) * sizeof(char));
	if(str_aux == NULL)
		return NULL;
	pos = 0;
	while(str[i] != '\0'){
		str_aux[pos] = str[i];
		pos++;
		i++;
	}
	str_aux[pos] = '\0';
	free(str);
	return str_aux;
}
