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
	int	x;
	int	y;

	mlx_mouse_get_pos(data->mlx, data->mlx_win, &x, &y);
	data->player->angle += (x - WIDTH / 2) * 0.0025;
	if (data->player->angle < 0)
		data->player->angle += 2 * M_PI;
	else if (data->player->angle >= 2 * M_PI)
		data->player->angle -= 2 * M_PI;
	mlx_mouse_move(data->mlx, data->mlx_win, WIDTH / 2, HEIGHT / 2);
	return (0);
}
