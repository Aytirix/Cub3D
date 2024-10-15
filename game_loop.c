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

int	game_loop(void *temp) // delete img - check pos - cast ray - update image
{
	t_data *data;
	data = temp;

	if (data->img_ptr)
		mlx_destroy_image(data->mlx, data->img_ptr);

	data->img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->buffer = (int *)mlx_get_data_addr(data->img_ptr, &data->bpp,
			&data->size_l, &data->endian);
	ray_casting(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_ptr, 0, 0);
	key_hook(data);
	mouse_move_hook(data);
	printf("data->player->angle = %f\n", data->player->angle);
	return (0);
}

void	check_collision(t_data *data)
{

	if (data->ray->wall_dist < COL_WALL)
		data->keys[0] = 0;
	else if (data->ray->wall_dist_b < COL_WALL)
		data->keys[1] = 0;
	else if (data->ray->wall_dist_l < COL_WALL)
		data->keys[2] = 0;
	else if (data->ray->wall_dist_r < COL_WALL)
		data->keys[3] = 0;
}

static void	calcul_rayon_hv(t_data *data, float modulo, double *var)
{
	float	horizontal_wall;
	float	vertical_wall;

	vertical_wall = vertical(data, modulo_pi(modulo));
	horizontal_wall = horizontal(data, modulo_pi(modulo));
	if (vertical_wall < horizontal_wall)
		*var = vertical_wall;
	else
		*var = horizontal_wall;
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
		calcul_rayon_hv(data, data->ray->ray_angle + M_PI,
			&data->ray->wall_dist_b);
		calcul_rayon_hv(data, data->ray->ray_angle - M_PI / 2,
			&data->ray->wall_dist_l);
		calcul_rayon_hv(data, data->ray->ray_angle + M_PI / 2,
			&data->ray->wall_dist_r);
		check_collision(data);
		render(data, cast);
		data->ray->ray_angle += (data->player->fov_rad / WIDTH);
		cast++;
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

	y -= 1;
	x_pos = floor(x / TILE_SIZE);
	y_pos = floor(y / TILE_SIZE);
	if (x < 0 || y < 0)
		return (0);
	if (y_pos >= data->map->map_h || x_pos >= data->map->map_w)
		return (0);
	if (data->map->map[y_pos] && x_pos <= ft_strlen(data->map->map[y_pos]))
	{
		if (data->map->map[y_pos][x_pos] == '1')
			return (0);
	}
	return (1); //$ OK
}

int	inter_wall_check(float angle, float *inter, float *incr, int i)
		//$ ajuste le signe de l incr + TILE_SIZE + Pixel
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
	return (1); //$ OK
}

int	check_direction(float incr, float angle, int i)
		// $ ajuste la direction de l increment
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
