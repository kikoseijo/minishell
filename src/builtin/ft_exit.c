/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:51:52 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/10/27 17:46:57 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_exit(t_model *model)
{
	int	ret;

	if (model->cmds[0]->num_args > 2)
	{
		ft_putstr_fd((char *)"exit: too many arguments\n", 2);
		return (-1);
	}
	else if (model->cmds[0]->args[1] == NULL)
		return (0);
	else if (ft_str_is_numeric(model->cmds[0]->args[1]))
	{
		ret = ft_atoi(model->cmds[0]->args[1]);
		return ((int)((unsigned char)ret));
	}
	else
	{
		ft_putstr_fd((char *)"exit: numeric argument required\n", 2);
		return (255);
	}
}
