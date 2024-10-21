/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:04:20 by hle-roux          #+#    #+#             */
/*   Updated: 2024/10/20 14:27:29 by hugo             ###   ########.fr       */
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
