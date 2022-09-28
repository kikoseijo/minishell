/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:54:12 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/23 15:28:36 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_export(char *input, char ***envp)
{
	char	*new_input[2];
	char	**new_env;
	int		i;
	char	key[100];

	i = 0;
	while (input[i] && (ft_isalnum(input[i]) || ft_isset(input[i],
				"_?")) && input[i] != '=')
	{
		key[i] = input[i];
		i++;
	}
	key[i] = '\0';
	if (input[i] != '=')
	{
		ft_putstr_fd((char *)"Invalid variable name\n", 2);
		return ;
	}
	ft_unset(key, envp);
	new_input[0] = input;
	new_input[1] = NULL;
	new_env = ft_array_join(*envp, new_input);
	ft_split_free(*envp);
	*envp = new_env;
}
