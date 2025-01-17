/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 01:03:41 by thmouty           #+#    #+#             */
/*   Updated: 2024/04/20 01:14:56 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

size_t	ft_whitespace(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] == '\t' || c[i] == '\n' || c[i] == '\v'
		|| c[i] == '\f' || c[i] == '\r')
		i++;
	return (i);
}
