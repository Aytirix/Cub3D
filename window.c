/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:28:52 by hle-roux          #+#    #+#             */
/*   Updated: 2024/10/20 00:28:50 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

void	create_window(t_data *data)
{
	data->mlx = mlx_init();

	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Hello world!");

	if (data->mlx == 0 || data->mlx_win == 0)
	{
		printf("ended\n");
		return ;
	}
		load_textures(data);


	printf("map_h %d \n\n\n", data->map->map_h);

	mlx_mouse_move(data->mlx, data->mlx_win, WIDTH / 2, HEIGHT / 2);
	mlx_loop_hook(data->mlx, &game_loop, data);
	mlx_hook(data->mlx_win, 2, 1L<<0, &key_press, data);
	mlx_hook(data->mlx_win, 3, 1L<<1, &key_release, data);
	mlx_mouse_hide(data->mlx, data->mlx_win);
	mlx_loop(data->mlx);
	printf("-- END -- \n");
}

