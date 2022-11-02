/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:08:50 by anramire          #+#    #+#             */
/*   Updated: 2022/11/02 21:15:07 by anramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	allocate_memory(char **str_aux, int tam)
{	
	*str_aux = (char *)ft_calloc(tam, sizeof(char));
	if (*str_aux == NULL)
		return (-1);
	return (0);
}
