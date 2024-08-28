/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:04:37 by hle-roux          #+#    #+#             */
/*   Updated: 2023/07/14 19:18:59 by hle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_puthexamaj(unsigned long long nb)
{
	char	*chaine;
	int		i;
	int		modulo;
	char	hexa[22];
	int		j;

	i = 0;
	chaine = "0123456789ABCDEF";
	if (nb == 0)
	{
		write (1, "0", 1);
		return (1);
	}
	while (nb >= 1)
	{
		modulo = nb % 16;
		hexa[i] = chaine[modulo];
		nb = nb / 16;
		i++;
	}
	j = i;
	while (j > 0)
		write(1, &hexa[--j], 1);
	return (i);
}

int	ft_puthexamin(unsigned long long nb)
{
	char	*chaine;
	int		i;
	int		modulo;
	char	hexa[22];
	int		j;

	i = 0;
	chaine = "0123456789abcdef";
	if (nb == 0)
	{
		write (1, "0", 1);
		return (1);
	}
	while (nb >= 1)
	{
		modulo = nb % 16;
		hexa[i] = chaine[modulo];
		nb = nb / 16;
		i++;
	}
	j = i;
	while (j > 0)
		write(1, &hexa[--j], 1);
	return (i);
}
