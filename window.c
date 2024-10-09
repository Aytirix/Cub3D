/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:28:52 by hle-roux          #+#    #+#             */
/*   Updated: 2024/10/09 18:50:55 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

void	create_window(t_data *data)
{
	data->mlx = mlx_init();

	data->mlx_win = mlx_new_window(data->mlx, 1900, 1080, "Hello world!");

	printf("map_h %d \n\n\n", data->map->map_h);

	mlx_loop_hook(data->mlx, &game_loop, data);
	mlx_key_hook(data->mlx_win, &key_hook, data);
	mlx_loop(data->mlx);
	printf("-- END -- \n");
}

