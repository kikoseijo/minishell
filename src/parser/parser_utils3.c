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

int	simp_quotes_core(t_cmd *command, char *str, int *pos, int *num_argument)
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
				command->args[*num_argument]
					= ft_concat_char(command->args[*num_argument],
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
	if (str[*pos] == '\'')
			quotes_found = 1;
	if(quotes_found == 0)
		return -1;
	return 1;
}
