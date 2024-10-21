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
	if (data->keys[0][1])
		forward(data);
	else if (data->keys[1][1])
		backward(data);
	else if (data->keys[2][1])
		left(data);
	else if (data->keys[3][1])
		right(data);
	return (0);
}

// 0 = Avancer
// 1 = Reculer
// 2 = Gauche
// 3 = Droite
// 4 = Menu
// 5 = + mini map
// 6 = - mini map
// 7 = gros zoom mini map
int	key_press(int key, t_data *data)
{
	printf("key = %d\n", key);
	if (key == 65307)
	{
		if (data->keys[4][1])
		{
			mlx_mouse_hide(data->mlx, data->mlx_win);
			mlx_mouse_move(data->mlx, data->mlx_win, WIDTH / 2, HEIGHT / 2);
			data->keys[4][1] = 0;
		}
		else
		{
			mlx_mouse_show(data->mlx, data->mlx_win);
			data->keys[4][1] = 1;
		}
	}
	if (data->keys[4][1])
		return (0);
	if (key == data->keys[0][0])
		data->keys[0][1] = 1;
	else if (key == data->keys[1][0])
		data->keys[1][1] = 1;
	else if (key == data->keys[2][0])
		data->keys[2][1] = 1;
	else if (key == data->keys[3][0])
		data->keys[3][1] = 1;
	else if (key == data->keys[7][0])
		data->keys[7][1] += 10;
	else if (key == data->keys[5][0] && data->keys[7][1] + 2 < 25)
		data->keys[7][1] += 2;
	else if (key == data->keys[6][0] && data->keys[7][1] - 2 > 0)
		data->keys[7][1] -= 2;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == 65470)
		free_all_stop(data, 0);
	if (data->keys[4][1])
		return (0);
	if (key == data->keys[0][0])
		data->keys[0][1] = 0;
	else if (key == data->keys[1][0])
		data->keys[1][1] = 0;
	else if (key == data->keys[2][0])
		data->keys[2][1] = 0;
	else if (key == data->keys[3][0])
		data->keys[3][1] = 0;
	else if (key == data->keys[7][0] && data->keys[7][1] - 10 > 0)
		data->keys[7][1] -= 10;
	return (0);
}
