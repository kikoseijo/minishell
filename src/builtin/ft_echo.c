/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:51:52 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/11/21 13:47:20 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_echo(int argc, char **args)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	if (argc > 1 && !ft_strncmp("-n", args[i], 3))
	{
		j = 1;
		i++;
	}
	while (i < argc)
	{
		ft_putstr_fd(args[i], 1);
		if (i < argc - 1)
			ft_putstr_fd((char *)" ", 1);
		i++;
	}
	if (j == 1 && argc > 2)
		ft_putstr_fd((char *)"\%", 1);
	ft_putstr_fd((char *)"\n", 1);
}
