/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:12:22 by hle-roux          #+#    #+#             */
/*   Updated: 2024/10/11 18:01:59 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"
#include<math.h>

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
}
