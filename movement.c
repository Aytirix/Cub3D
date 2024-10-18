/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:41:10 by hle-roux          #+#    #+#             */
/*   Updated: 2024/10/11 20:13:08 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(t_data *data)
{
	if (data->keys[0])
		forward(data);
	else if (data->keys[1])
		backward(data);
	else if (data->keys[2])
		left(data);
	else if (data->keys[3])
		right(data);
	return (0);
}

int key_press(int key, t_data *data)
{
	if ((key == 119 || key == 65362) && data->ray->wall_dist > COL_WALL)
		data->keys[0] = 1;
	else if ((key == 115 || key == 65364) && data->ray->wall_dist_b > COL_WALL)
		data->keys[1] = 1;
	else if ((key == 97 || key == 65361) && data->ray->wall_dist_l > COL_WALL)
		data->keys[2] = 1;
	else if ((key == 100 || key == 65363) && data->ray->wall_dist_r > COL_WALL)
		data->keys[3] = 1;
	if (key == 65307 || key == 65307)
		free_all_stop(data, 0);
	return (0);
}

int key_release(int key, t_data *data)
{
	if (key == 119 || key == 65362)
		data->keys[0] = 0;
	else if (key == 115 || key == 65364)
		data->keys[1] = 0;
	else if (key == 97 || key == 65361)
		data->keys[2] = 0;
	else if (key == 100 || key == 65363)
		data->keys[3] = 0;
	if (key == 65307 || key == 65307)
		free_all_stop(data, 0);
	return (0);
}

void	forward(t_data *data)
{
	data->player->p_x += cos(data->player->angle) * 5;
	data->player->p_y += sin(data->player->angle) * 5;
}


void	backward(t_data *data)
{
	data->player->p_x -= cos(data->player->angle) * 5;
	data->player->p_y -= sin(data->player->angle) * 5;
}

void	right(t_data *data)
{
	data->player->p_x += cos(data->player->angle + M_PI / 2) * 5;
	data->player->p_y += sin(data->player->angle + M_PI / 2) * 5;
}

void	left(t_data *data)
{
	data->player->p_x -= cos(data->player->angle + M_PI / 2) * 5;
	data->player->p_y -= sin(data->player->angle + M_PI / 2) * 5;
}

int	mouse_move_hook(t_data *data)
{
	int x;
    int y;

    mlx_mouse_get_pos(data->mlx, data->mlx_win, &x, &y);
	data->player->angle += (x - WIDTH / 2) * 0.0025;
	if (data->player->angle < 0)
		data->player->angle += 2 * M_PI;
	else if (data->player->angle >= 2 * M_PI)
		data->player->angle -= 2 * M_PI;
	mlx_mouse_move(data->mlx, data->mlx_win, WIDTH / 2, HEIGHT / 2);
	return (0);
}
