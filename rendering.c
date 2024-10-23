/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:49:44 by hugo              #+#    #+#             */
/*   Updated: 2024/10/11 20:13:38 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_data *data, int cast)
{
	float	wall_size;
	float	wall_top;
	float	wall_bottom;

	data->ray->cast = cast;
	data->ray->wall_dist *= cos(modulo_pi(data->ray->ray_angle
				- data->player->angle));
	if (data->ray->wall_dist <= COL_WALL)
		data->ray->wall_dist = COL_WALL;
	wall_size = (TILE_SIZE / data->ray->wall_dist) * ((WIDTH / 2)
			/ tan(data->player->fov_rad / 2));
	wall_bottom = (HEIGHT / 2) + (wall_size / 2);
	wall_top = (HEIGHT / 2) - (wall_size / 2);
	if (wall_bottom > HEIGHT)
		wall_bottom = HEIGHT;
	if (wall_top < 0)
		wall_top = 0;
	texture_to_wall(data, wall_bottom, wall_top, wall_size);
	put_ceiling(data, cast, HEIGHT / 2 - wall_size / 2,
		data->map->ceilling_color);
	put_floor(data, cast, HEIGHT / 2 + wall_size / 2, data->map->floor_color);
}

void	put_ceiling(t_data *data, int x, int y, int color)
{
	while (y > 0)
	{
		put_pixel(data, x, y, color);
		y--;
	}
}

void	put_floor(t_data *data, int x, int y, int color)
{
	while (y < HEIGHT)
	{
		put_pixel(data, x, y, color);
		y++;
	}
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	if (x < 0)
		return ;
	if (y < 0)
		return ;
	if (x > WIDTH)
		return ;
	if (y > HEIGHT)
		return ;
	data->buffer[y * WIDTH + x] = color;
}
