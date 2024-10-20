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

void	move_player(t_data *data, double move_angle, double wall_dist_check)
{
	double	new_x;
	double	new_y;
	double	slide_angle;

	calcul_rayon_hv(data, data->player->angle, &data->ray->wall_dist);
	calcul_rayon_hv(data, data->player->angle + M_PI, &data->ray->wall_dist_b);
	calcul_rayon_hv(data, data->player->angle - M_PI / 2,
		&data->ray->wall_dist_l);
	calcul_rayon_hv(data, data->player->angle + M_PI / 2,
		&data->ray->wall_dist_r);
	new_x = data->player->p_x + cos(move_angle) * P_SPEED;
	new_y = data->player->p_y + sin(move_angle) * P_SPEED;
	if (wall_dist_check > COL_WALL)
	{
		data->player->p_x = new_x;
		data->player->p_y = new_y;
	}
	// else
	// {
	// 	slide_angle = move_angle + M_PI / 2;
	// 	double wall_dist_slide;
	// 	calcul_rayon_hv(data, slide_angle, &wall_dist_slide);
	// 	if (wall_dist_slide > COL_WALL)
	// 	{
	// 		data->player->p_x += cos(slide_angle) * P_SPEED / 2;
	// 		data->player->p_y += sin(slide_angle) * P_SPEED / 2;
	// 	}
	// 	else
	// 	{
	// 		slide_angle -= M_PI; // On inverse la direction de glissement
	// 		calcul_rayon_hv(data, slide_angle, &wall_dist_slide);
	// 		if (wall_dist_slide > COL_WALL)
	// 		{
	// 			data->player->p_x += cos(slide_angle) * P_SPEED / 2;
	// 			data->player->p_y += sin(slide_angle) * P_SPEED / 2;
	// 		}
	// 	}
	// }
}

void	forward(t_data *data)
{
	move_player(data, data->player->angle, data->ray->wall_dist);
}

void	backward(t_data *data)
{
	move_player(data, data->player->angle + M_PI, data->ray->wall_dist_b);
}

void	right(t_data *data)
{
	move_player(data, data->player->angle + M_PI / 2, data->ray->wall_dist_r);
}

void	left(t_data *data)
{
	move_player(data, data->player->angle - M_PI / 2, data->ray->wall_dist_l);
}

int	mouse_move_hook(t_data *data)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(data->mlx, data->mlx_win, &x, &y);
	data->player->angle += (x - WIDTH / 2) * MOVE_SPEED;
	if (data->player->angle < 0)
		data->player->angle += 2 * M_PI;
	else if (data->player->angle >= 2 * M_PI)
		data->player->angle -= 2 * M_PI;
	mlx_mouse_move(data->mlx, data->mlx_win, WIDTH / 2, HEIGHT / 2);
	return (0);
}
