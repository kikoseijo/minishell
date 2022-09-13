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
