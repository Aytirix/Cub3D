/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annex3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:02:10 by hle-roux          #+#    #+#             */
/*   Updated: 2023/07/14 19:19:02 by hle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_strchr(const char *str, int c)
{
	int			i;
	char		*cast;
	signed char	l;

	l = (signed char)c;
	cast = (char *)str;
	i = 0;
	while (cast[i])
	{
		if (cast[i] == l)
			return (cast + i);
		i++;
	}
	if (l == '\0')
		return (cast + i);
	return (NULL);
}

int	ft_intlen(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	if (n != 0)
	{
		while (n <= -1 || n >= 1)
		{
			n = n / 10;
			i++;
		}
	}
	else if (n == 0)
		i++;
	return (i);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
