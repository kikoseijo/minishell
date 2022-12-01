/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:13:49 by anramire          #+#    #+#             */
/*   Updated: 2022/12/01 16:07:16 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_is_located(int *i, int init, char *aux, char **str)
{
	int		j;
	int		located;
	char	*env2;

	j = 0;
	located = 0;
	while (g_envp[j])
	{
		if (ft_strncmp(aux, g_envp[j], (*i) - init) == 0)
		{
			located = 1;
			free(aux);
			aux = *str;
			env2 = ft_substr(g_envp[j], (*i) - init + 1, ft_strlen(g_envp[j]));
			*str = ft_strjoin(*str, env2);
			free(aux);
			free(env2);
			break ;
		}
		j++;
	}
	return (located);
}

void	main_loop_dollar(char *copy_str, int *i, char **str, t_model *model)
{
	int		init;
	char	*dollar;
	char	*aux;

	(*i)++;
	init = (*i);
	while (copy_str[*i] != ' ' && copy_str[*i] != '$' && copy_str[*i] != '\0')
		(*i)++;
	dollar = ft_itoa(model->dollar);
	aux = *str;
	*str = ft_strjoin(*str, dollar);
	free(dollar);
	free(aux);
}

void	main_loop(char *copy_str, int *i, char **str)
{
	int		init;
	char	*aux;
	int		located;

	(*i)++;
	init = (*i);
	while (copy_str[*i] != ' ' && copy_str[*i] != '$' && copy_str[*i] != '\0')
		(*i)++;
	aux = ft_substr(copy_str, init, (*i) - init + 1);
	located = check_is_located(i, init, aux, str);
	if (located == 0)
		free(aux);
}

int	check_empty_spaces(char *str)
{
	int	i;
	int	value;

	value = -1;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && (str[i] != '\t'))
		{
			value = 0;
			break ;
		}
		i++;
	}
	return (value);
}
