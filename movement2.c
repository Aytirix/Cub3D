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
	if (data->settings->forward->press)
		forward(data);
	else if (data->settings->backward->press)
		backward(data);
	else if (data->settings->left->press)
		left(data);
	else if (data->settings->right->press)
		right(data);
	return (0);
}

int	key_press(int key, t_data *data)
{
	if (key == data->settings->menu->key)
	{
		if (data->settings->menu->press)
		{
			mlx_mouse_hide(data->mlx, data->mlx_win);
			mlx_mouse_move(data->mlx, data->mlx_win, WIDTH / 2, HEIGHT / 2);
			data->settings->menu->press = 0;
		}
		else
		{
			mlx_mouse_show(data->mlx, data->mlx_win);
			data->settings->menu->press = 1;
		}
	}
	if (data->settings->menu->press)
	{
		check_update_lisent(data, key);
		return (0);
	}
	if (key == data->settings->forward->key)
		data->settings->forward->press = 1;
	else if (key == data->settings->backward->key)
		data->settings->backward->press = 1;
	else if (key == data->settings->left->key)
		data->settings->left->press = 1;
	else if (key == data->settings->right->key)
		data->settings->right->press = 1;
	else if (key == data->settings->big_zoom->key)
		data->settings->big_zoom->press += 10;
	else if (key == data->settings->zoom_in->key && data->settings->big_zoom->press
		+ 2 < 25)
		data->settings->big_zoom->press += 2;
	else if (key == data->settings->zoom_out->key && data->settings->big_zoom->press
		- 2 > 0)
		data->settings->big_zoom->press -= 2;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == 65470)
		free_all_stop(data, 0);
	if (data->settings->menu->press)
		return (0);
	if (key == data->settings->forward->key)
		data->settings->forward->press = 0;
	else if (key == data->settings->backward->key)
		data->settings->backward->press = 0;
	else if (key == data->settings->left->key)
		data->settings->left->press = 0;
	else if (key == data->settings->right->key)
		data->settings->right->press = 0;
	else if (key == data->settings->big_zoom->key
		&& data->settings->big_zoom->press - 10 > 0)
		data->settings->big_zoom->press -= 10;
	return (0);
}
