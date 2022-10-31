/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:30:16 by anramire          #+#    #+#             */
/*   Updated: 2022/10/31 22:20:32 by cmac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_error(int error, t_model *model)
{
	if (error == -1)
	{
		ft_printf("Error: Bad command syntax!!!\n");
		free_model(model, 0);
		return (1);
	}
	else if (error == -2)
	{
		ft_printf("Error: Quotes not closed!!!\n");
		free_model(model, 0);
		return (1);
	}
	return (0);
}
