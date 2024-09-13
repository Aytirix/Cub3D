/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:12:22 by hle-roux          #+#    #+#             */
/*   Updated: 2024/09/13 18:21:08 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"
#include<math.h>

void	get_ply_pos(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	i = 0;


	while (data->map->map[i])
	{
		j = 0;
		while(data->map->map[i][j])
		{
			if(data->map->map[i][j] != '0' && data->map->map[i][j] != '1' && data->map->map[i][j] != '\n')
			{
				data->map->p_x_location = j + 1;
				data->map->p_y_location = i + 1;
				printf("x:y location = %d:%d\n", data->map->p_x_location, data->map->p_y_location)	;
				data->player->p_x = (j + 1) * TILE_SIZE + TILE_SIZE / 2;
				data->player->p_y = (i + 1) * TILE_SIZE + TILE_SIZE / 2;
				printf("p_x:p_y pixel = %d:%d\n", data->player->p_x, data->player->p_y)	;
				get_start_angle(data, data->map->map[i][j]);
				printf("Pole %f \n", data->player->angle);
			}
			j++;
		}
		i++;
	}
	data->map->map_h = i;
	data->map->map_w = j - 1;
}

void	get_start_angle(t_data *data, char c)
{
	if (c == 'N')
		data->player->angle = 3 * M_PI / 2;
	else if (c == 'W')
		data->player->angle = M_PI;
	else if (c == 'S')
		data->player->angle = (M_PI) / 2;
	else if (c == 'E')
		data->player->angle = 0;

	data->player->fov_rad = (FOV * M_PI) / 180;
	printf("FOV en rad : %f \n", data->player->fov_rad); // rad = cercle trigo

}
