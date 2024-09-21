/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:04:20 by hle-roux          #+#    #+#             */
/*   Updated: 2024/09/21 09:28:42 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

void	ft_error(char* message)
{
	ft_printf("ERROR : %s \n", message);
}


float	modulo_pi(float x)
{
	while (x < 0 || x > 2 * M_PI)
	{
		if (x < 0)
			x = x + (2 * M_PI);
		else if (x > 2 * M_PI)
			x = x - 2 * M_PI;
	}
	return x;
}
