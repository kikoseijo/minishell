/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 18:24:02 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/06/07 10:50:10 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static void	ft_print_hex(t_print *model, unsigned long long nb)
{
	if (nb >= 16)
		ft_print_hex(model, (unsigned long long)nb / 16);
	model->str_len += 1;
	ft_putchar_fd("0123456789abcdef"[nb % 16], 1);
}

void	ft_print_p(t_print *model, unsigned long long nb)
{
	ft_putstr_fd("0x", 1);
	model->str_len += 2;
	ft_print_hex(model, nb);
	model->str++;
}
