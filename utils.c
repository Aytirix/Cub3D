/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:04:20 by hle-roux          #+#    #+#             */
/*   Updated: 2024/10/21 18:54:26 by hle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

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

void free_all_stop(t_data *data, int code)
{
	int	i;
	mlx_destroy_image(data->mlx, data->map->img_NO->img_ptr);

	free(data->map->img_NO->name);
	free(data->map->img_SO->name);
	free(data->map->img_WE->name);
	free(data->map->img_EA->name);

	free(data->map->img_NO);
	free(data->map->img_SO);
	free(data->map->img_WE);
	free(data->map->img_EA);
	i = -1;
	while (data->map->map[++i])
		free(data->map->map[i]);
	free(data->map->map);
	exit(code);
}
