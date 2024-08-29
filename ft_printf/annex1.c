/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annex1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 18:54:42 by hle-roux          #+#    #+#             */
/*   Updated: 2024/08/29 15:16:38 by hle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_putchar(char c)
{
	if (c == 0)
	{
		write(1, "\0", 1);
		return (1);
	}
	else
		write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
		write(1, &str[i++], 1);
	return (i);
}

int	ft_putnbr(int nb)
{
	int		buff;

	buff = nb;
	if (nb >= 0 && nb <= 9)
	{
		nb = nb + 48;
		write (1, &nb, 1);
	}
	else if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		nb *= -1;
	}
	else if ((nb < 0) && (nb != -2147483648))
	{
		write(1, "-", 1);
		ft_putnbr(nb * (-1));
	}
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	return (ft_intlen(buff));
}

int	ft_putunbr(unsigned int nb)
{
	unsigned int	buff;

	buff = nb;
	if (/*nb >= 0 &&*/ nb <= 9)
	{
		nb = nb + 48;
		write (1, &nb, 1);
	}
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	if (nb > 1836311903)
		return (10);
	return (ft_intlen(buff));
}

int	ft_putptr(unsigned long long ptr)
{
	int	i;

	i = 0;
	write(1, "0x", 2);
	i = i + 2;
	i = i + ft_puthexamin(ptr);
	return (i);
}
