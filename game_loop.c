/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:43:41 by hle-roux          #+#    #+#             */
/*   Updated: 2024/09/04 19:12:48 by hle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

#include <time.h>

// will be looped on indefinitly until key pressed where key hook will be called

int	game_loop(void *data) // delete img - check pos - cast ray - update image
{
	t_data *temp;
	temp = data;

	int i;
	int j;
	int x;

	i = rand() % 1000;
	j = rand() % 500;


	mlx_pixel_put(temp->mlx, temp->mlx_win, i, j, x);

	//ray_casting(temp);


	return 0;
}


void	ray_casting(t_data *temp)
{
	int	i;

	i = 0;

	while (i < 1900) // boucle pour chaque rayon - i = 0 --> Rayon.0
	{
		temp->ray->wall_dist = 0;

		vertical(temp, pi_angle(temp->player->angle));
		horizontal(temp, pi_angle(temp->player->angle));

		//calculate dist wall

		// rendering the ray_line

	}

}

float	vertical(temp, pi_angle(temp->player->angle))
{

}


float	horizontal(temp, pi_angle(temp->player->angle)) //! A COMPRENDRE ET FINIR
{
	//$ get h_inter et x_inter ???
	//*		h_inter = (p_y / tile_size) * tile						-->
	//*		x_inter = p_x + (h_inter - p_y) / tan(ray_angle)		--> trigo ok
	//
	//$ get x_step et y_step
	//*		y_step = tile_size								--> ez
	//*		x_step = tile_size / tan(ray_angle) 			--> trigo ok


	return
}

// il faut faire correspondre les 2 mesures, le FOV et le S_W de l ecran


//$	----------------------- INCREMENT ---------------------------
// 	 increment = (FOV / S_W 1900)
//	 incrr_rad = (1.15192 / 1900)
//	 incrr_rad = 0.00060627368 		--> increment en radian pour chaque rayons/pixel

//	 incrr_angle = 0.0347368421		--> increment en angle pour chaque rayon/pixel

//$ ----------------------- FIRST ANGLE -------------------------
//	Curr_Angle - FOV/2 (en rad)

// S_W = 0-1900 = rayons
// FOV = 66 deg = 1,15192 =



//? NOTE :
