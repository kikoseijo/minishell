/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:51:52 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/23 09:38:27 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_echo(int argc, char **args)
{
	int	i;
	int	n;

	n = 0;
	i = 1;
	if (argc > 1 && !ft_strncmp("-n", args[i], 3))
	{
		n = 1;
		i++;
	}
	while (i < argc)
	{
		ft_putstr_fd(args[i], 1);
		if (i < argc - 1)
			ft_putstr_fd((char *)" ", 1);
		i++;
	}
	if (!n)
		ft_putstr_fd((char *)"\n", 1);
}
