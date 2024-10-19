/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:04:20 by hle-roux          #+#    #+#             */
/*   Updated: 2024/10/11 18:58:28 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	modulo_pi(float x)
{
	while (x < 0 || x > 2 * M_PI)
	{
		if (x < 0)
			x = x + (2 * M_PI);
		else if (x > 2 * M_PI)
			x = x - 2 * M_PI;
	}
	return (x);
}

void	free_all_stop(t_data *data, int code)
{
	int	i;

	free(data->map->img_no);
	free(data->map->img_so);
	free(data->map->img_we);
	free(data->map->img_ea);
	i = -1;
	while (data->map->map && data->map->map[++i])
		free(data->map->map[i]);
	free(data->map->map);
	exit(code);
}
