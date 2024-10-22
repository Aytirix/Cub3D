/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:49:44 by hugo              #+#    #+#             */
/*   Updated: 2024/10/22 20:15:49 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_data *data, int cast)
{
	float	wall_size;
	float	wall_top;
	float	wall_bottom;
	int		i;

	i = 0;
	data->ray->cast = cast;
	data->ray->wall_dist *= cos(modulo_pi(data->ray->ray_angle
				- data->player->angle));
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

float calcul_x_offset(t_data *data, t_texture* txtr)
{
	float x_offset;

	if (data->ray->is_horizontal)
		x_offset = fmodf((data->ray->h_x * ((float)txtr->width / (float)TILE_SIZE)), (float)txtr->width);
	else
		x_offset = fmodf(data->ray->v_y * ((float)txtr->width / (float)TILE_SIZE), (float)txtr->width);
	return (x_offset);
}

float calcul_y_offset(int wall_top, int wall_size, float increment)
{
	float y_offset;

	y_offset = ((float)wall_top - (HEIGHT / 2) + ((float)(wall_size) / 2)) * increment;
	if (y_offset < 0)
		y_offset = 0;

	return y_offset;
}

t_texture*	get_side_texture(t_data *data)
{
	if (data->ray->is_horizontal)
	{
		if (0 < data->ray->ray_angle && data->ray->ray_angle < M_PI)
			return data->map->img_SO;
		else
			return data->map->img_NO;
	}
	else
	{
		if (M_PI / 2 < data->ray->ray_angle && data->ray->ray_angle < 3 * M_PI / 2)
			return data->map->img_EA;
		else
			return data->map->img_WE;
	}
}

void	texture_to_wall(t_data *data, int wall_bottom, int wall_top, int wall_size)
{
	float		x_offset;
	float		y_offset;
	float		increment;
	int			pixel_pos;
	int		*arr;
	t_texture	*txtr;

	txtr = get_side_texture(data);
	increment = (float)txtr->height / (float)(wall_size);
	x_offset = calcul_x_offset(data, txtr);
	y_offset = calcul_y_offset(wall_top, wall_size, increment);
	arr = (int *)txtr->txtr_ptr;

	while (wall_top <= wall_bottom)
	{
		pixel_pos = (int)y_offset * txtr->width + (int)x_offset;
		put_pixel(data, data->ray->cast, wall_top, arr[pixel_pos]);
		y_offset += increment;
		wall_top ++;
	}
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


