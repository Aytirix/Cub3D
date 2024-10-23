/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:43:41 by hle-roux          #+#    #+#             */
/*   Updated: 2024/10/11 20:22:42 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

void	draw_square(t_data *data, double x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->settings->big_zoom->press)
	{
		j = 0;
		while (j < data->settings->big_zoom->press)
		{
			if ((int)x * data->settings->big_zoom->press + j < WIDTH && (int)y
				* data->settings->big_zoom->press + i < HEIGHT)
				data->buffer[((int)y * data->settings->big_zoom->press + i + 10)
					* WIDTH + (int)x * data->settings->big_zoom->press + j
					+ 10] = color;
			j++;
		}
		i++;
	}
}

void	calcul_rayon_hv(t_data *data, float modulo, double *var, int iteration)
{
	float	horizontal_wall;
	float	vertical_wall;
	int		i;

	i = 0;
	while (i < iteration)
	{
		vertical_wall = vertical(data, modulo_pi(modulo));
		horizontal_wall = horizontal(data, modulo_pi(modulo));
		if (vertical_wall < horizontal_wall)
			*var = vertical_wall;
		else
			*var = horizontal_wall;
		if (*var < COL_WALL)
			break ;
		modulo += 0.10;
		i++;
	}
}

float	horizontal(t_data *temp, float angle)
{
	float	x_inter_coord;
	float	y_inter_coord;
	float	incr_x;
	float	incr_y;
	int		pixel_wall;

	angle = modulo_pi(angle);
	incr_y = TILE_SIZE;
	incr_x = incr_y / tan(angle);
	y_inter_coord = floor(temp->player->p_y / TILE_SIZE) * TILE_SIZE;
	pixel_wall = inter_wall_check(angle, &y_inter_coord, &incr_y, 0);
	x_inter_coord = temp->player->p_x + (y_inter_coord - temp->player->p_y)
		/ tan(angle);
	incr_x *= check_direction(incr_x, angle, 0);
	while (walled(x_inter_coord, y_inter_coord - pixel_wall, temp))
	{
		x_inter_coord += incr_x;
		y_inter_coord += incr_y;
	}
	return (sqrt(pow(x_inter_coord - temp->player->p_x, 2) + pow(y_inter_coord
				- temp->player->p_y, 2)));
}

float	vertical(t_data *temp, float angle)
{
	float	x_inter_coord;
	float	y_inter_coord;
	float	incr_x;
	float	incr_y;
	int		pixel_wall;

	angle = modulo_pi(angle);
	incr_x = TILE_SIZE;
	incr_y = incr_x * tan(angle);
	x_inter_coord = floor(temp->player->p_x / TILE_SIZE) * TILE_SIZE;
	pixel_wall = inter_wall_check(angle, &x_inter_coord, &incr_x, 1);
	y_inter_coord = temp->player->p_y + (x_inter_coord - temp->player->p_x)
		* tan(angle);
	incr_y *= check_direction(incr_y, angle, 1);
	while (walled(x_inter_coord - pixel_wall, y_inter_coord, temp))
	{
		x_inter_coord += incr_x;
		y_inter_coord += incr_y;
	}
	return (sqrt(pow(x_inter_coord - temp->player->p_x, 2) + pow(y_inter_coord
				- temp->player->p_y, 2)));
}

int	walled(float x, float y, t_data *data)
{
	int	x_pos;
	int	y_pos;

	x_pos = floor(x / TILE_SIZE);
	y_pos = floor(y / TILE_SIZE);
	if (x_pos < 0 || y_pos < 0 || y_pos >= data->map->map_h
		|| x_pos >= data->map->map_w)
		return (0);
	if (y_pos >= data->map->map_h || x_pos >= data->map->map_w)
		return (0);
	if (data->map->map[y_pos] && x_pos <= (int)ft_strlen(data->map->map[y_pos]))
	{
		if (data->map->map[y_pos][x_pos] == '1')
			return (0);
	}
	return (1);
}
