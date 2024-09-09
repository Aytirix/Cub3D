/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:41:10 by hle-roux          #+#    #+#             */
/*   Updated: 2024/09/09 17:41:22 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

int	key_hook(int key, t_data *data)
{
	printf("In key hook - %d ---------------\n", key);
	if (key == 65307)
		ft_close(data);
	else if (key == 115)
		clear_img(data);

	return 0;
}


void	clear_img(t_data *data)
{
	int i = 0;
	int j = 0;

	int x;

	x = rand() & 0xff;
	x |= (rand() & 0xff) << 8;
	x |= (rand() & 0xff) << 16;
	x |= (rand() & 0xff) << 24;

	mlx_clear_window(data->mlx, data->mlx_win);


	while (i < 1900)
	{
		j = 0;
		while (j < 1000)
			{
				mlx_pixel_put(data->mlx, data->mlx_win, i, j, x);
				j++;
			}
		i++;

	}
}

int	ft_close(t_data *data)
{
	printf("dwdwdwdwdwdwdwdwdwdwdwdw \n");
	mlx_destroy_window(data->mlx, data->mlx_win);


	//ft_freee(&data);
	exit(0);
	return (0);
}
