/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:49:44 by hugo              #+#    #+#             */
/*   Updated: 2024/10/15 16:27:28 by hle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

void	render(t_data *data, int cast)
{
	float	wall_size;
	float	wall_top;
	float	wall_bottom;
	int		i;

	i = 0;
	data->ray->cast = cast;


	data->ray->wall_dist *= cos(modulo_pi(data->ray->ray_angle - data->player->angle)); // fix the fisheye
	wall_size = (TILE_SIZE / data->ray->wall_dist) * ((1900 / 2) / tan(data->player->fov_rad / 2));

	wall_bottom = (1080 / 2) + (wall_size / 2);
	wall_top = (1080 / 2) - (wall_size / 2);

	if (wall_bottom > 1080)
			wall_bottom = 1080;
	if (wall_top < 0)
			wall_top = 0;


	while (i < wall_size / 2)
	{
		put_pixel(data, cast, 1080 / 2 - i, 0xB24512);
		put_pixel(data, cast, 1080 / 2 + i, 0xB24512);
		i++;
	}

	put_ceiling(data, cast, 1080 / 2 - wall_size / 2, 0xB0D3F3); // Yellow
	put_floor(data, cast, 1080 / 2 + wall_size / 2, 0xDEA063); // blanc

	i = 0;
	while (i++ < 1080)
	{
		put_pixel(data, 1485, i, 0xFFFFFF);
		put_pixel(data, 1490, i, 0xFFFFFF);
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
	while (y < 1080)
	{
		put_pixel(data, x, y, color);
		y++;
	}
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	if (x < 0)
		return;
	if (y < 0)
		return;
	if (x > 1900)
		return;
	if (y > 1080)
		return;

	data->buffer[y * 1900 + x] = color;
}

// render walls, floor and ceiling

// use this to get faster rendering ?
//		mlx_new_image | void	*mlx_new_image(void *mlx_ptr,int width,int height);
//		mlx_get_data_addr
//		mlx_put_image_to_window | int mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y);

