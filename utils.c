/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:04:20 by hle-roux          #+#    #+#             */
/*   Updated: 2024/09/04 17:51:49 by hle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

void	ft_error(char* message)
{
	ft_printf("ERROR : %s \n", message);
}


float	pi_angle(float x)
{
	if (x < 0)
		x =+ (2 * M_PI);

	if (x > 2 * M_PI)
		x =- 2 * M_PI;

	return x;
}
