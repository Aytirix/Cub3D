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

//$ DEVNOTES

//* RAYCASTING		OK (1 bug)
//* OPTIMISATION 	OK
//* TEXTURES		TODO <<--
//* MOUVEMENTS		DOING

static void	mini_map(t_data *data)
{
	int	x;
	int	y;

	x = -1;
	while (data->map->map[++x])
	{
		y = -1;
		while (data->map->map[x][++y])
		{
			if (data->map->map[x][y] == '1' || data->map->map[x][y] == ' ')
				draw_square(data, y, x, 0x000000);
			else if (data->map->map[x][y] == '0')
				draw_square(data, y, x, data->map->floor_color);
			else if (ft_strchr("NSEW", data->map->map[x][y]))
				draw_square(data, y, x, 0x00ff00);
		}
		while (y < data->map->map_w)
		{
			draw_square(data, y, x, 0x000000);
			y++;
		}
	}
	draw_square(data, data->player->p_x / TILE_SIZE, data->player->p_y
		/ TILE_SIZE, 0xff0000);
}

int	game_loop(t_data *data)
{
	if (data->img_ptr)
	{
		mlx_destroy_image(data->mlx, data->img_ptr);
		data->img_ptr = NULL;
	}
	data->img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->buffer = (int *)mlx_get_data_addr(data->img_ptr, &data->bpp,
			&data->size_l, &data->endian);
	ray_casting(data);
	if (data->settings->menu->press == 0)
		mini_map(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_ptr, 0, 0);
	if (data->settings->menu->press)
		draw_menu(data);
	key_hook(data);
	mouse_move_hook(data);
	return (0);
}

void	ray_casting(t_data *data)
{
	int	cast;

	cast = 0;
	data->ray->ray_angle = data->player->angle - (data->player->fov_rad / 2);
	while (cast < WIDTH)
	{
		data->ray->color_flag = 0;
		calcul_rayon_hv(data, data->ray->ray_angle, &data->ray->wall_dist);
		render(data, cast);
		data->ray->ray_angle += (data->player->fov_rad / WIDTH);
		cast++;
	}
}

int	inter_wall_check(float angle, float *inter, float *incr, int i)
{
	if (i == 0)
	{
		if (angle >= 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*incr *= -1;
	}
	else if (i == 1)
	{
		if (!(angle >= M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*incr *= -1;
	}
	return (1);
}

int	check_direction(float incr, float angle, int i)
{
	if (i == 0)
	{
		if ((angle > (M_PI / 2) && angle < (3 * M_PI) / 2) && incr > 0)
			return (-1);
		else if (!(angle > (M_PI / 2) && angle < (3 * M_PI) / 2) && incr < 0)
			return (-1);
	}
	else if (i == 1)
	{
		if (angle > 0 && angle < M_PI && incr < 0)
			return (-1);
		else if (!(angle > 0 && angle < M_PI) && incr > 0)
			return (-1);
	}
	return (1);
}
