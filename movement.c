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

#include"cub3d.h"

int	key_hook(int key, t_data *data)
{
	if (key == 122)
		forward(data);
	else if (key == 113)
		right(data);
	else if (key == 100)
		left(data);
	else if (key == 115)
		backward(data);

	if (key == 65307)
		ft_close(data);

	return 0;
}


int	ft_close(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
	return (0);
}

void forward(t_data *data)
{
	data->player->p_y += 10;
}

void backward(t_data *data)
{
	data->player->p_y -= 10;
}

void right(t_data *data)
{
	data->player->p_x += 10;
}

void left(t_data *data)
{
	data->player->p_x -= 10;
}
