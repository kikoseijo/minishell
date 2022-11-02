/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:54:12 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/11/02 20:56:24 by anramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	wrong_variable(char *key)
{
	ft_putstr_fd((char *)"Invalid variable name\n", 2);
	free(key);
	return ;
}

void	ft_export(char *input)
{
	char	**new_input;
	char	**new_env;
	char	*key;
	int		i;

	new_input = (char **)ft_calloc(2, sizeof(char *));
	key = (char *)ft_calloc(ft_strlen(input) + 1, sizeof(char));
	i = 0;
	while (input[i] && (ft_isalnum(input[i]) || ft_isset(input[i], "_?"))
		&& input[i] != '=')
	{
		key[i] = input[i];
		i++;
	}
	if (input[i] != '=')
		return (wrong_variable(key));
	ft_unset(key);
	free(key);
	new_input[0] = input;
	new_env = ft_array_join(g_envp, new_input);
	ft_free_array(g_envp);
	ft_free_array(new_input);
	g_envp = new_env;
}
