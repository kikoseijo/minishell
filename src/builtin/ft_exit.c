/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:51:52 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/09/29 18:11:00 by cmac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_exit(t_model *model)
{
	int	ret;

	if (model->cmds[0]->num_args + 1 > 2)
	{
		ft_putstr_fd((char *)"exit: too many arguments\n", 2);
		return (-1);
	}
	else if (model->cmds[0]->args[1] == NULL)
	{
		free_model(model);
		return (0);
	}
	else if (ft_str_is_numeric(model->cmds[0]->args[1]))
	{
		ret = ft_atoi(model->cmds[0]->args[1]);
		return ((int)((unsigned char)ret));
	}
	else
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return (-1);
	}
}
