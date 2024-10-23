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

#include "../cub3d.h"

void	move_player(t_data *data, double move_angle, double wall_dist_check)
{
	double	new_x;
	double	new_y;

	new_x = data->player->p_x + cos(move_angle) * data->player->p_speed;
	new_y = data->player->p_y + sin(move_angle) * data->player->p_speed;
	if (wall_dist_check > COL_WALL)
	{
		if (walled(new_x, data->player->p_y, data))
			data->player->p_x = new_x;
		if (walled(data->player->p_x, new_y, data))
			data->player->p_y = new_y;
	}
}

void	forward(t_data *data)
{
	calcul_rayon_hv(data, data->player->angle, &data->ray->wall_dist_f);
	move_player(data, data->player->angle, data->ray->wall_dist_f);
}

void	backward(t_data *data)
{
	calcul_rayon_hv(data, data->player->angle + M_PI, &data->ray->wall_dist_b);
	move_player(data, data->player->angle + M_PI, data->ray->wall_dist_b);
}

void	right(t_data *data)
{
	calcul_rayon_hv(data, data->player->angle + M_PI / 2,
		&data->ray->wall_dist_r);
	move_player(data, data->player->angle + M_PI / 2, data->ray->wall_dist_r);
}

void	left(t_data *data)
{
	calcul_rayon_hv(data, data->player->angle - M_PI / 2,
		&data->ray->wall_dist_l);
	move_player(data, data->player->angle - M_PI / 2, data->ray->wall_dist_l);
}
