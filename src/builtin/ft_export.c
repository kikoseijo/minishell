/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:54:12 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/23 09:38:32 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	len_table(char **table)
{
	int	len;

	len = 0;
	while (table && table[len])
		len++;
	return (len);
}

static char	**join_split(char **a, char **b)
{
	int		size;
	char	**ret;
	int		i;
	int		j;

	size = len_table(a) + len_table(b) + 1;
	ret = (char **)malloc(size * sizeof(char *));
	if (!ret)
		return (NULL);
	i = -1;
	while (a && a[++i])
		ret[i] = ft_strdup(a[i]);
	j = 0;
	while (b && b[j])
		ret[i++] = ft_strdup(b[j++]);
	ret[i] = NULL;
	return (ret);
}

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
	new_env = join_split(*envp, new_input);
	ft_split_free(*envp);
	*envp = new_env;
}
