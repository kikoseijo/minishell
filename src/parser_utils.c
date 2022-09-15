#include "../inc/minishell.h"


char *clean_white_spaces(char *str)
{
	char *str_aux;
	int end;
	int pos;
	int i;

	pos = 0;
	while(str[pos] == ' ')
		pos++;
	end = pos;
	while(str[end] != '\0')
		end++;
	str_aux = (char *)malloc((end - pos + 1) * sizeof(char));
	if(str_aux == NULL)
		return NULL;
	i = 0;
	while(pos < end)
	{
		str_aux[i] = str[pos];
		pos++;
		i++;
	}
	free(str);
	str_aux[i] = '\0';
	return str_aux;
}


int get_arguments_with_quotes(t_simple_command *command, char *str, int pos, int *num_argument)
{
	(*num_argument)++;
	pos++;
	command->args[*num_argument] = (char *)malloc(sizeof(char));	
	command->args[*num_argument][0] = '\0';
	
	while(str[pos] != '"'){
		command->args[*num_argument] = ft_concat_char(command->args[*num_argument], str[pos]);
		pos++;
	}
	pos++;
	return pos;
}

//Function to show list of commands

void	show_list(t_model *command_line){
	
	int	i;
	int	n;

	n = 0;
	while(n < (command_line->num_commands)){
	i = 0;
		ft_printf("<------------------------->\n");
		ft_printf("command: %s\n", command_line->commands[n]->command);
		while(command_line->commands[n]->args[i] != NULL){
				ft_printf("args[%d]: %s\n", i, command_line->commands[n]->args[i]);
				i++;
			}
		i = 0;
		while(i < command_line->commands[n]->num_simple_out){
			ft_printf("simple output file[%d]: %s\n", i, command_line->commands[n]->fd_simple_out[i]);
			i++;
		}

		i = 0;
		while(i < command_line->commands[n]->num_double_out){
			ft_printf("double output file[%d]: %s\n", i, command_line->commands[n]->fd_double_out[i]);
			i++;
		}

		i = 0;
		while(i < command_line->commands[n]->num_simple_in){
			ft_printf("simple input file[%d]: %s\n", i, command_line->commands[n]->fd_simple_in[i]);
			i++;
		}
		ft_printf("pipe: %d\n", command_line->commands[n]->pipe);
		n++;
	}
}

void	init_command(t_simple_command **new_command){

	*new_command = (t_simple_command *)malloc(sizeof(t_simple_command));
	(*new_command)->command = (char *)malloc(sizeof(char));
	(*new_command)->command[0] = '\0';
	(*new_command)->args = (char **)malloc(200 * sizeof(char *));
	(*new_command)->pipe = 0;
	(*new_command)->fd_simple_out = (char **)malloc(100 * sizeof(char *));
	(*new_command)->num_simple_out = 0;
	(*new_command)->fd_double_out = (char **)malloc(100 * sizeof(char *));
	(*new_command)->num_double_out = 0;
	(*new_command)->fd_simple_in = (char **)malloc(100 * sizeof(char *));
	(*new_command)->num_simple_in = 0;
}

int	get_output_file(t_simple_command *command, char *str, int pos)
{
	int end;
	char *file;
	int i;
	end = pos;
	while(str[end] != '\0' && (str[end] != ' ') && (str[end] != '|') && (str[end] != ';') && (str[end] != '>'))
		end++;
	command->fd_simple_out[command->num_simple_out] = (char *)malloc((end - pos + 1) * sizeof(char));
	if(command->fd_simple_out[command->num_simple_out] == NULL)
		return -1;
	i = 0;
	while(str[pos] != '\0' && (str[pos] != ' ') && (str[pos] != '|') && (str[pos] != ';') && (str[pos] != '>'))
	{
		command->fd_simple_out[command->num_simple_out][i] = str[pos];
		pos++;
		i++;
	}
	command->fd_simple_out[command->num_simple_out][i] = '\0';
	(command->num_simple_out)++;
	ft_printf("end: %s\n", &str[end]);
	return end;
}

int	get_double_file(t_simple_command *command, char *str, int pos)
{
	int end;
	char *file;
	int i;
	end = pos;
	while(str[end] != '\0' && (str[end] != ' ') && (str[end] != '|') && (str[end] != ';') && (str[end] != '>'))
		end++;
	command->fd_double_out[command->num_double_out] = (char *)malloc((end - pos + 1) * sizeof(char));
	if(command->fd_double_out[command->num_double_out] == NULL)
		return -1;
	i = 0;
	while(str[pos] != '\0' && (str[pos] != ' ') && (str[pos] != '|') && (str[pos] != ';') && (str[pos] != '>'))
	{
		command->fd_double_out[command->num_double_out][i] = str[pos];
		pos++;
		i++;
	}
	command->fd_double_out[command->num_double_out][i] = '\0';
	(command->num_double_out)++;
	ft_printf("end double: %s\n", &str[end]);
	return end;
}
