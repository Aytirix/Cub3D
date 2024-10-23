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

void	load_textures(t_data *data)
{
	data->map->img_no->img_ptr = mlx_xpm_file_to_image(data->mlx,
			data->map->img_no->name, &data->map->img_no->width,
			&data->map->img_no->height);
	data->map->img_so->img_ptr = mlx_xpm_file_to_image(data->mlx,
			data->map->img_so->name, &data->map->img_so->width,
			&data->map->img_so->height);
	data->map->img_we->img_ptr = mlx_xpm_file_to_image(data->mlx,
			data->map->img_we->name, &data->map->img_we->width,
			&data->map->img_we->height);
	data->map->img_ea->img_ptr = mlx_xpm_file_to_image(data->mlx,
			data->map->img_ea->name, &data->map->img_ea->width,
			&data->map->img_ea->height);
	data->map->img_no->txtr_ptr = mlx_get_data_addr(data->map->img_no->img_ptr,
			&data->map->img_no->bpp, &data->map->img_no->size_line,
			&data->map->img_no->endian);
	data->map->img_so->txtr_ptr = mlx_get_data_addr(data->map->img_so->img_ptr,
			&data->map->img_so->bpp, &data->map->img_so->size_line,
			&data->map->img_so->endian);
	data->map->img_we->txtr_ptr = mlx_get_data_addr(data->map->img_we->img_ptr,
			&data->map->img_we->bpp, &data->map->img_we->size_line,
			&data->map->img_we->endian);
	data->map->img_ea->txtr_ptr = mlx_get_data_addr(data->map->img_ea->img_ptr,
			&data->map->img_ea->bpp, &data->map->img_ea->size_line,
			&data->map->img_ea->endian);
}

t_texture	*get_side_texture(t_data *data)
{
	if (data->ray->is_horizontal)
	{
		if (0 < data->ray->ray_angle && data->ray->ray_angle < M_PI)
			return (data->map->img_so);
		else
			return (data->map->img_no);
	}
	else
	{
		if (M_PI / 2 < data->ray->ray_angle && data->ray->ray_angle < 3 * M_PI
			/ 2)
			return (data->map->img_ea);
		else
			return (data->map->img_we);
	}
}

void	texture_to_wall(t_data *data, int wall_bottom, int wall_top,
		int wall_size)
{
	float		x_offset;
	float		y_offset;
	float		increment;
	int			*arr;
	t_texture	*txtr;

	txtr = get_side_texture(data);
	increment = (float)txtr->height / (float)(wall_size);
	x_offset = calcul_x_offset(data, txtr);
	y_offset = calcul_y_offset(wall_top, wall_size, increment);
	arr = (int *)txtr->txtr_ptr;
	while (wall_top <= wall_bottom)
	{
		put_pixel(data, data->ray->cast, wall_top, arr[(int)y_offset
			* txtr->width + (int)x_offset]);
		y_offset += increment;
		wall_top++;
	}
}

float	calcul_x_offset(t_data *data, t_texture *txtr)
{
	float	x_offset;

	if (data->ray->is_horizontal)
		x_offset = fmodf((data->ray->h_x * ((float)txtr->width
						/ (float)TILE_SIZE)), (float)txtr->width);
	else
		x_offset = fmodf(data->ray->v_y * ((float)txtr->width
					/ (float)TILE_SIZE), (float)txtr->width);
	return (x_offset);
}

float	calcul_y_offset(int wall_top, int wall_size, float increment)
{
	float	y_offset;

	y_offset = ((float)wall_top - (HEIGHT / 2) + ((float)(wall_size) / 2))
		* increment;
	if (y_offset < 0)
		y_offset = 0;
	return (y_offset);
}
