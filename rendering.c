/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:49:44 by hugo              #+#    #+#             */
/*   Updated: 2024/10/04 19:37:28 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

//$ 	--- DEVNOTE NEXT ---

//* -	BUG MOITIE RENDERING PARALISIE--> OK
//* - OPTIMISATION
//* - DECALAGE des cubes

void	render(t_data *data, int cast)
{
	float	wall_size;
	float	wall_top;
	float	wall_bottom;
	//int		i;

	//i = 0;
	data->ray->wall_dist *= cos(modulo_pi(data->ray->ray_angle - data->player->angle)); // fix the fisheye
	wall_size = (TILE_SIZE / data->ray->wall_dist) * ((1900 / 2) / tan(data->player->fov_rad / 2));

	wall_bottom = (1080 / 2) + (wall_size / 2);
	wall_top = (1080 / 2) - (wall_size / 2);

	if (wall_bottom > 1080)
			wall_bottom = 1080;
	if (wall_top < 0)
			wall_top = 0;

	mlx_pixel_put(data->mlx, data->mlx_win, cast, wall_top, 0xFF0000);
	mlx_pixel_put(data->mlx, data->mlx_win, cast, wall_bottom, 0xFF0000);


	// while (i < wall_size / 2)
	// {
	// 	put_pixel(data, cast, 1080 / 2 - i, 0xAA0000);
	// 	put_pixel(data, cast, 1080 / 2 + i, 0xAA0000);
	// 	i++;
	// }
	//put_ceiling(data, cast, 1080 / 2 - wall_size / 2, 0xAAAA00); // Yellow
	//put_floor(data, cast, 1080 / 2 + wall_size / 2, 0xAAAAAA); // blanc

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
	mlx_pixel_put(data->mlx, data->mlx_win, x, y, color);
}

// render walls, floor and ceiling

// use this to get faster rendering ?
//		mlx_new_image
//		mlx_get_data_addr
//		mlx_put_image_to_window
