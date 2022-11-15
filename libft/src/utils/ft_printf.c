/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:16:32 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/06/07 10:50:13 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	is_special_char(char c)
{
	int		i;
	char	special_chars[10];

	special_chars[0] = 'c';
	special_chars[1] = 's';
	special_chars[2] = 'p';
	special_chars[3] = 'd';
	special_chars[4] = 'i';
	special_chars[5] = 'u';
	special_chars[6] = 'x';
	special_chars[7] = 'X';
	special_chars[8] = '%';
	special_chars[9] = '\0';
	i = 0;
	while (special_chars[i])
	{
		if (c == special_chars[i])
			return (1);
		i++;
	}
	return (0);
}

static void	ft_print_s(t_print *m, char *str)
{
	if (str == NULL)
	{
		ft_putstr_fd("(null)", 1);
		m->str_len += ft_strlen("(null)");
	}
	else
	{
		ft_putstr_fd((char *)str, 1);
		m->str_len += ft_strlen(str);
	}
	m->str++;
}

static void	ft_print_c(t_print *m, int c)
{
	ft_putchar_fd((char)c, 1);
	m->str++;
	m->str_len++;
}

static void	ft_parse_item(t_print *m)
{
	m->str++;
	if (*m->str == 'c')
		ft_print_c(m, va_arg(m->args, int));
	else if (*m->str == '%')
		ft_print_c(m, '%');
	else if (*m->str == 's')
		ft_print_s(m, va_arg(m->args, char *));
	else if (*m->str == 'x' || *m->str == 'X')
		ft_print_x(m, va_arg(m->args, unsigned long long));
	else if (*m->str == 'p')
		ft_print_p(m, va_arg(m->args, unsigned long long));
	else if (*m->str == 'd' || *m->str == 'i')
		ft_print_int(m, va_arg(m->args, int));
	else if (*m->str == 'u')
		ft_print_uint(m, va_arg(m->args, unsigned int));
}

int	ft_printf(const char *format, ...)
{
	t_print	*model;
	int		res;

	model = (t_print *)malloc(sizeof(t_print));
	if (!model)
		return (0);
	va_start(model->args, format);
	model->str = (char *)format;
	model->str_len = 0;
	while (*model->str)
	{
		if (*model->str == '%' && is_special_char(*(model->str + 1)))
			ft_parse_item(model);
		else
			ft_print_c(model, *model->str);
	}
	va_end(model->args);
	res = model->str_len;
	if (model)
		free(model);
	return (res);
}
