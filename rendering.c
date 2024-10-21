/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:49:44 by hugo              #+#    #+#             */
/*   Updated: 2024/10/21 18:53:34 by hle-roux         ###   ########.fr       */
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

	texture_to_wall(data, wall_bottom, wall_top);

	put_ceiling(data, cast, HEIGHT / 2 - wall_size / 2,
		data->map->ceilling_color);
	put_floor(data, cast, HEIGHT / 2 + wall_size / 2, data->map->floor_color);

}

float calcul_x_offset(t_data *data)
{
	float x_offset;

	printf("v_y : %f\n", data->ray->v_y);
	printf("h_x : %f\n", data->ray->h_x);


	if (data->ray->is_horizontal)
	{
		x_offset = (int)fmodf(data->ray->h_x * (data->map->img_NO->width / TILE_SIZE), data->map->img_NO->width);
		printf("horiz\n");
	}
	else
	{
		x_offset = (int)fmodf(data->ray->v_y * (data->map->img_NO->width / TILE_SIZE), data->map->img_NO->width);
		printf("verti\n");
	}
	return (x_offset);
}



void	texture_to_wall(t_data *data, int wall_bottom, int wall_top) //$ recup la texture
{
	//$stocker chaque image dans une structure dans laquelle il y aura leur get_data_addr
	float		x_offset;
	float		y_offset;
	float		facteur_y;
	int			color;
	int			pixel_pos;
	uint32_t		*arr;

	y_offset = 0;
	x_offset = calcul_x_offset(data);
	arr = (uint32_t *)data->map->img_NO->txtr_ptr;
	facteur_y = (float)data->map->img_NO->height / (wall_bottom - wall_top);

	printf("CAST : %d\n", data->ray->cast);
	printf("x_offset : %f\n\n", x_offset);

	while (wall_top <= wall_bottom)
	{
		pixel_pos = (int)y_offset * data->map->img_NO->width + (int)x_offset;
		color = arr[pixel_pos];
		put_pixel(data, data->ray->cast, wall_top, color);
		y_offset += facteur_y;
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


