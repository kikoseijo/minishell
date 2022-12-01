/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:54:36 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/11/30 16:24:12 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_cmd *cmd)
{
	char	**envp;

	envp = g_envp;
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	cmd->model->dollar = 0;
}
