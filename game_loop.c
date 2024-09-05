/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:43:41 by hle-roux          #+#    #+#             */
/*   Updated: 2024/09/05 18:35:48 by hugo             ###   ########.fr       */
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

	i = rand() % 1900;
	j = rand() % 1000;



	mlx_pixel_put(temp->mlx, temp->mlx_win, i, j, 0xFF0000);

	ray_casting(temp);


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

float	vertical(t_data *temp, float angle)
{

}


float	horizontal(t_data *temp, float angle) //! A COMPRENDRE ET FINIR
{
	//float x_inter;	//$ Position X de l intersection horizontale, sera tjrs sur une inter horiz
	float y_inter;	//$ Position Y de l intersection horizontale, sera tjrs sur une inter horiz
	float incr_x;	//? Valeur x du vecteur a incrementer pour aller a l intersection suivante
	float incr_y;	//? Valeur y du vecteur a incrementer pour aller a l intersection suivante
	//int  pixel_wall;		// Pixel a additionner +1 ou -1 pour check le wall

	angle -= 0.60;

	//$ get x_step et y_step
	incr_y = TILE_SIZE;
	incr_x = incr_y / tan(angle);

	//$ get h_inter et x_inter ???
	y_inter = floor(temp->player->p_y / TILE_SIZE) * TILE_SIZE;

	//pixel_wall = check_crossing();

	printf("\np_x : %d\n p_y : %d\ny_inter : %f\nx_incr : %f\ny_incr : %f\n------------------------",temp->player->p_x, temp->player->p_y, y_inter, incr_x, incr_y);



	return 0;
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
