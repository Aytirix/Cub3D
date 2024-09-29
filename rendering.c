/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:49:44 by hugo              #+#    #+#             */
/*   Updated: 2024/09/29 18:52:20 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

void	render(t_data *data, int cast) //! DEBUT DU RENDERING
{
	float	wall_size;
	float	wall_top;
	float	wall_bottom;
	int		i;

	i = 0;
	printf("CAST NUMBER : %d\n", cast);
	data->ray->wall_dist *= cos(modulo_pi(data->ray->ray_angle - data->player->angle)); // fix the fisheye
	wall_size = (TILE_SIZE / data->ray->wall_dist) * ((1900 / 2) / tan(data->player->fov_rad / 2));
	printf("WALL SIZE : %f\n", wall_size);

	while (i < wall_size / 2)
	{
		put_pixel(data, cast, 1080 / 2 - i, 0xFF0000);
		put_pixel(data, cast, 1080 / 2 + i, 0xFF0000);
		i++;
	} //! Fonctionne mais quand avance == bug de wall qui persiste
	put_ceiling(data, cast, 1080 / 2 - wall_size / 2, 0xFFFF00); // Yellow
	put_floor(data, cast, 1080 / 2 + wall_size / 2, 0xFFFFFF); // blanc


}

void	put_ceiling(t_data *data, int x, int y, int color)
{
	printf("Y CEILLING : %d\n\n", y);

	while (y > 0)
	{
		put_pixel(data, x, y, color);
		y--;
	}


}

void	put_floor(t_data *data, int x, int y, int color)
{
	printf("Y FLOOR : %d\n\n", y);
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
