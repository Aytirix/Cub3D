/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:49:44 by hugo              #+#    #+#             */
/*   Updated: 2024/10/20 23:31:18 by hugo             ###   ########.fr       */
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

	wall_bottom = (HEIGHT / 2) + (wall_size / 2);	// le + grand
	wall_top = (HEIGHT / 2) - (wall_size / 2);		// le plus petit
	if (wall_bottom > HEIGHT)
		wall_bottom = HEIGHT;
	if (wall_top < 0)
		wall_top = 0;

	texture_to_wall(data, wall_bottom, wall_top);

	put_ceiling(data, cast, HEIGHT / 2 - wall_size / 2,
		data->map->ceilling_color);
	put_floor(data, cast, HEIGHT / 2 + wall_size / 2, data->map->floor_color);

}

int calcul_x_offset(t_data *data)
{
	int x_offset;

	if (data->ray->is_horizontal)
	{
		x_offset = (int)data->ray->h_x % 30;
	}
	else
	{
		x_offset = (int)data->ray->v_y % 30;
	}
	return (x_offset);
	//y_offset = 0;

//	int test = (wall_top - (HEIGHT / 2) + ((wall_bottom - wall_top) / 2)) ;

	// facteur_y = 64 / (wall_bottom - wall_top);
	// x_offset = calcul_x_offset(data);
	// y_offset += facteur_y;
}



void	texture_to_wall(t_data *data, int wall_bottom, int wall_top) //$ recup la texture
{
	//$stocker chaque image dans une structure dans laquelle il y aura leur get_data_addr
	// int		x_offset;
	// int		y_offset;
	// float	facteur_y;
	int color;
	int pixel_pos;
	uint32_t		*arr;
	//pixel_pos = wall_top_int * data->map->img_NO->width + data->ray->cast * (data->map->img_NO->bpp / 8);
	arr = (uint32_t *)data->map->img_NO->txtr_ptr;

	color = 16685312;
	int i = 0;
	while (arr[i])
		i++;
	printf("I : %d\n",i);
	while (wall_top <= wall_bottom)
	{
		color = arr[wall_top * data->map->img_NO->size_line + (data->ray->cast * (data->map->img_NO->bpp / 8))];
		//color = *(int*)(data->map->img_NO->txtr_ptr + pixel_pos);
		printf("wall top : %d\n", data->map->img_NO->bpp / 8);
		put_pixel(data, data->ray->cast, wall_top, color);
		wall_top++;
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

