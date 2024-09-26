/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:49:44 by hugo              #+#    #+#             */
/*   Updated: 2024/09/26 18:54:59 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

void	render(t_data *data, int cast) //! DEBUT DU RENDERING
{
	float	wall_size;
	float	wall_top;
	float	wall_bottom;


	printf("CAST NUMBER : %d\n", cast);
	data->ray->wall_dist *= cos(modulo_pi(data->ray->ray_angle - data->player->angle)); // fix the fisheye
//! Comprendre le thales cf Medium


}

// render walls, floor and ceiling

// use this to get faster rendering ?
//		mlx_new_image
//		mlx_get_data_addr
//		mlx_put_image_to_window
