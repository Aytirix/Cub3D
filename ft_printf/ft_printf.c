/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:18:45 by hle-roux          #+#    #+#             */
/*   Updated: 2023/07/14 19:19:04 by hle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	exam_arg(char flag, va_list ap)
{
	if (flag == 'i' || flag == 'd')
		return (ft_putnbr(va_arg (ap, int)));
	else if (flag == 'x')
		return (ft_puthexamin(va_arg (ap, unsigned int)));
	else if (flag == 'X')
		return (ft_puthexamaj(va_arg (ap, unsigned int)));
	else if (flag == 'u')
		return (ft_putunbr(va_arg (ap, unsigned int)));
	else if (flag == 'c')
		return (ft_putchar(va_arg (ap, int)));
	else if (flag == 's')
		return (ft_putstr(va_arg (ap, char *)));
	else if (flag == 'p')
		return (ft_putptr(va_arg (ap, unsigned long long)));
	else if (flag == '%')
		write (1, "%", 1);
	return (1);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%' && ft_strchr("cspdiuxX%", str[i + 1]))
		{
			len = len + exam_arg(str[i + 1], ap);
			i++;
		}
		else
			len = len + ft_putchar(str[i]);
		i++;
	}
	va_end(ap);
	return (len);
}
