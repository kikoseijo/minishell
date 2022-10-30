/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:54:12 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/10/30 20:15:46 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** static void	wrong_variable(char *key)
** {
** 	ft_putstr_fd((char *)"Invalid variable name\n", 2);
** 	free(key);
** 	return ;
** }
**
** void	ft_export(char *input, char **envp)
** {
** 	char	**new_input;
** 	char	**new_env;
** 	char	*key;
** 	int		i;
**
** 	new_input = (char **)ft_calloc(2, sizeof(char *));
** 	key = (char *)ft_calloc(ft_strlen(input), sizeof(char));
** 	i = 0;
** 	while (input[i] && (ft_isalnum(input[i]) || ft_isset(input[i], "_?"))
** 		&& input[i] != '=')
** 	{
** 		key[i] = input[i];
** 		i++;
** 	}
** 	if (input[i] != '=')
** 		return (wrong_variable(key));
** 	ft_unset(key, envp);
** 	new_input[0] = input;
** 	new_env = ft_array_join(envp, new_input);
** 	ft_split_free(envp);
** 	ft_split_free(new_input);
** 	envp = new_env;
** }
*/

void	ft_export(char *entry, char **envp)
{
	char	*new_entry[2];
	char	**new_env;
	int		i;
	char	key[100];

	i = 0;
	while (entry[i] && (ft_isalnum(entry[i]) || ft_isset(entry[i], "_?"))
		&& entry[i] != '=')
	{
		key[i] = entry[i];
		i++;
	}
	key[i] = '\0';
	if (entry[i] != '=')
	{
		ft_putstr_fd("Invalid variable name\n", 2);
		return ;
	}
	ft_unset(key, envp);
	new_entry[0] = entry;
	new_entry[1] = NULL;
	new_env = ft_array_join(envp, new_entry);
	ft_split_free(envp);
	ft_split_free(new_entry);
	envp = new_env;
}
