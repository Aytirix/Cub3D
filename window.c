/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:28:52 by hle-roux          #+#    #+#             */
/*   Updated: 2024/09/03 18:21:24 by hle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

void	create_window(t_data *data)
{
	data->mlx = mlx_init(1920, 1080, "Cub3D", 0);

	data->mlx_win = mlx_new_window(data->mlx, 1920, 1080, "Hello world!");

	int i = 0;

	while (i < 1000)
	{
		mlx_pixel_put(data->mlx, data->mlx_win, i, 500, 0xFF0000);
		i++;
	}


	//mlx_loop(data->mlx);


}
