/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:30:16 by anramire          #+#    #+#             */
/*   Updated: 2022/09/28 22:26:21 by anramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_error(int error, t_model *model)
{
	if (error == -1)
	{
		ft_printf("Error: Bad command syntax!!!\n");
		model = NULL;
		return (1);
	}
	else if (error == -2)
	{
		ft_printf("Error: Quotes not closed!!!\n");
		model = NULL;
		return (1);
	}
	return (0);
}
