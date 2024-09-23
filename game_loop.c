/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:43:41 by hle-roux          #+#    #+#             */
/*   Updated: 2024/09/23 18:28:35 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

#include <time.h>

// will be looped on indefinitly until key pressed where key hook will be called

int	game_loop(void *data) // delete img - check pos - cast ray - update image
{
	t_data *temp;
	temp = data;



	ray_casting(temp);

	mlx_destroy_window(temp->mlx, temp->mlx_win);


	return 0;
}


void	ray_casting(t_data *temp)
{
	int	i;

	i = 0;

	//while (i < 1900) // boucle pour chaque rayon - i = 0 --> Rayon.0
	//{
		temp->ray->wall_dist = 0;
		//! Set l angle du rayon != angle player

		vertical(temp, modulo_pi(temp->player->angle));
		horizontal(temp, modulo_pi(temp->player->angle)); //! pas de le premier rayon !!

		//calculate dist wall

		// rendering the ray_line
		i++; //! + incrementer l angle du rayon
	//}

}

float	horizontal(t_data *temp, float angle)
{
	//! M_PI = infini car jamais d intersection avec lignes horizontales quand PI = 0
	float x_inter_coord;
	float y_inter_coord;
	float incr_x;
	float incr_y;
	int  pixel_wall;

	angle = modulo_pi(angle);

	incr_y = TILE_SIZE;
	incr_x = incr_y / tan(angle);

	y_inter_coord = floor(temp->player->p_y / TILE_SIZE) * TILE_SIZE;
	x_inter_coord = temp->player->p_x +  (temp->player->p_y - y_inter_coord) / tan(angle);

	//printf("\ny_inter : %f\n\n", y_inter_coord);


	pixel_wall = inter_wall_check(angle, &y_inter_coord, &incr_y, 1);
	incr_x *= check_direction(incr_x, angle, 0); // ? protected here (cf med)

	while (walled(x_inter_coord, y_inter_coord - pixel_wall, temp))
	{
		x_inter_coord += incr_x;
		y_inter_coord += incr_y;
	}

	//printf("x_wall = %f\ny_wall = %f------------------\n", x_inter_coord, y_inter_coord);
//	printf("\nincr_x : %f\nincr_y : %f\npixel_wall : %d\n angle : %f\n\n",incr_x, incr_y, pixel_wall, angle);
//	printf("dist = %f\n", sqrt(pow(x_inter_coord - temp->player->p_x, 2) + pow(y_inter_coord - temp->player->p_y, 2)));
//	printf("=================================================================\n\n");
	return (sqrt(pow(x_inter_coord - temp->player->p_x, 2) + pow(y_inter_coord - temp->player->p_y, 2)));
}

float	vertical(t_data *temp, float angle) //! LEs valeurs sont ok mais CHECk les signes + PIXEL
{
	float x_inter_coord; //! COORDONEE !!
	float y_inter_coord;
	float incr_x;
	float incr_y;
	int  pixel_wall;

	printf("\n	-- VERTICAL --\n");

	angle = modulo_pi(angle);
	angle -= M_PI / 4;

	printf("\n\nANGLE : %f\n\n", angle);
	printf("x_pos : %d\ny_pos : %d\n\n", temp->player->p_x, temp->player->p_y);

	incr_x = TILE_SIZE;
	incr_y = incr_x * tan(angle);
	printf("\nINCR_X : %f", incr_x);
	printf("\nINCR_Y : %f\n\n", incr_y);



	x_inter_coord = floor(temp->player->p_x / TILE_SIZE) * TILE_SIZE;
	y_inter_coord = temp->player->p_y +  (temp->player->p_x - x_inter_coord) * tan(angle);
	printf("x_inter : %f\n", x_inter_coord);
	printf("y_inter : %f\n\n", y_inter_coord);

	pixel_wall = inter_wall_check(angle, &y_inter_coord, &incr_y, 1);
	incr_x *= check_direction(incr_x, angle, 0); // ? protected here (cf med)

	while (walled(x_inter_coord, y_inter_coord - pixel_wall, temp))
	{
		x_inter_coord += incr_x;
		y_inter_coord += incr_y;
	}

	printf("x_wall = %f\ny_wall = %f------------------\n", x_inter_coord, y_inter_coord);
	printf("\nincr_x : %f\nincr_y : %f\npixel_wall : %d\n angle : %f\n\n",incr_x, incr_y, pixel_wall, angle);
	printf("dist = %f\n", sqrt(pow(x_inter_coord - temp->player->p_x, 2) + pow(y_inter_coord - temp->player->p_y, 2)));
	printf("=================================================================\n\n");
	return (sqrt(pow(x_inter_coord - temp->player->p_x, 2) + pow(y_inter_coord - temp->player->p_y, 2)));
}

int	walled(float x, float y, t_data *data)
{
	int x_pos;
	int y_pos;

	x_pos = floor(x / TILE_SIZE);
	y_pos = floor(y / TILE_SIZE);

	if (x < 0 || y < 0)
		return 0;
	if (y_pos >= data->map->map_h || x_pos >= data->map->map_w)
		return 0;

	if (data->map->map[y_pos] && x_pos <= ft_strlen(data->map->map[y_pos]))
		if (data->map->map[y_pos][x_pos] == '1')
			return 0;

	return 1;
}

int	inter_wall_check(float angle, float *inter,float *incr, int i)//! Finir la partie vertical
{
	if (i == 1)
	{
		if (angle >= 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*incr *= -1;
	}
	else if (i == 0)
	{

	}
	return (1);
}

int	check_direction(float incr, float angle, int i) // $ ajuste la direction de l increment
{
	if (i == 0)
	{
		if((angle > (M_PI / 2) && angle < (3 * M_PI) / 2) && incr > 0)
			return (-1);
		else if(!(angle > (M_PI / 2) && angle < (3 * M_PI) / 2) && incr < 0)
			return(-1);
		else
			return (1);
	}
	else if (i == 1)
	{
		if(angle > 0 && angle < M_PI && incr > 0)
			return (-1);
		else if(!(angle > 0 && angle < M_PI) && incr < 0)
			return (-1);
		else
			return (1);
	}
	return 1;
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
