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

int	key_press(int key, t_data *data)
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

int	key_release(int key, t_data *data)
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
