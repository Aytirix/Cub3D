/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:04:20 by hle-roux          #+#    #+#             */
/*   Updated: 2024/09/09 16:39:41 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

void	ft_error(char* message)
{
	ft_printf("ERROR : %s \n", message);
}


float	modulo_pi(float x)
{
	if (x < 0)
		x =+ (2 * M_PI);

	if (x > 2 * M_PI)
		x =- 2 * M_PI;

	return x;
}
