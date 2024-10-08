/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:43:41 by hle-roux          #+#    #+#             */
/*   Updated: 2024/10/08 18:37:10 by hugo             ###   ########.fr       */
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

	//ft_close(data);

	return 0;
}


void	ray_casting(t_data *temp)
{
	int	cast;
	float horizontal_wall;
	float vertical_wall;

	cast = 0;
	temp->ray->ray_angle = temp->player->angle - (temp->player->fov_rad / 2);
	while (cast < 1900)
	{
		temp->ray->color_flag = 0;


		vertical_wall = vertical(temp, modulo_pi(temp->ray->ray_angle));
		horizontal_wall = horizontal(temp, modulo_pi(temp->ray->ray_angle));

		if (temp->ray->cast == 1350)
		{
			printf("CAST  = %d\n", temp->ray->cast);
			printf("ANGLE  = %f\n", temp->ray->ray_angle);
			printf("P_X : %d, P_Y : %d\n", temp->player->p_x, temp->player->p_y);
		}

		if (vertical_wall < horizontal_wall)
		{
			if ( temp->ray->cast == 1350)
				printf("----->> V <<-------\n\n");
			temp->ray->wall_dist = vertical_wall;
		}
		else
		{
			if (temp->ray->cast == 1350)
				printf("----->> H <<-------\n\n");
			temp->ray->wall_dist = horizontal_wall;
		}
		float wall_size_v;
		float wall_size_h;
		wall_size_h = (TILE_SIZE / horizontal_wall) * ((1900 / 2) / tan(temp->player->fov_rad / 2));
		wall_size_v = (TILE_SIZE / vertical_wall) * ((1900 / 2) / tan(temp->player->fov_rad / 2));

		if (cast == 1350)
		{
//		 	printf("CAST  = %dl\n", cast);

			printf("V DIST = %f\n", vertical_wall);
			printf("H DIST = %f\n\n", horizontal_wall);
//			printf("ANGLE en PI : %f.PI\n\n", temp->ray->ray_angle / 3.1415);
//			printf("=================================================================\n\n");
		}

		mlx_pixel_put(temp->mlx, temp->mlx_win, cast, wall_size_h, 0x0000FF);
		mlx_pixel_put(temp->mlx, temp->mlx_win, cast, wall_size_v, 0x00FF00);

		int i = 0;
		while (i < 1080)
		{
			mlx_pixel_put(temp->mlx, temp->mlx_win, 1300, i, 0xFFFFFF);
			mlx_pixel_put(temp->mlx, temp->mlx_win, 1350, i, 0xFFFFFF);
			mlx_pixel_put(temp->mlx, temp->mlx_win, 950, i, 0xFFFFFF);
			mlx_pixel_put(temp->mlx, temp->mlx_win, 1210, i, 0xFFFFFF);
			i++;
		}

		render(temp, cast);
		cast++;
		temp->ray->ray_angle += (temp->player->fov_rad / 1900);

	}

}

float	horizontal(t_data *temp, float angle) //! PROBLEME ICI <<---------------
{
	float x_inter_coord;
	float y_inter_coord;
	float incr_x;
	float incr_y;
	int  pixel_wall;

	angle = modulo_pi(angle);

	incr_y = TILE_SIZE;
	incr_x = incr_y / tan(angle);

	y_inter_coord = floor(temp->player->p_y / TILE_SIZE) * TILE_SIZE;
	pixel_wall = inter_wall_check(angle, &y_inter_coord, &incr_y, 0); //! PB ici, dans cet ordre V, ici marche pas
	x_inter_coord = temp->player->p_x +  (y_inter_coord - temp->player->p_y) / tan(angle);
	if (temp->ray->cast == 1350)
	{
		printf(" --- P_X  = %d\n", temp->player->p_x);
		printf(" --- incr_X  = %f\n", incr_x);
		printf(" --- X_inter  = %f\n", x_inter_coord);
		printf(" --- Y_inter  = %f\n", y_inter_coord);
	}
		incr_x *= check_direction(incr_x, angle, 0);

	while (walled(x_inter_coord, y_inter_coord - pixel_wall, temp, 'H')) //! PB AVANT ICI
	{
		x_inter_coord += incr_x;
		y_inter_coord += incr_y;
		if (temp->ray->cast == 1350)
		{
			printf("CAST  = %d - %c\n", temp->ray->cast, 'H');
			printf(" --- incr_X  = %f\n", incr_x);
			printf("x_inter = %f\ny_inter = %f\n\n", x_inter_coord, y_inter_coord);
		}
	}
	return (sqrt(pow(x_inter_coord - temp->player->p_x, 2) + pow(y_inter_coord - temp->player->p_y, 2)));
}

float	vertical(t_data *temp, float angle)
{
	float x_inter_coord;
	float y_inter_coord;
	float incr_x;
	float incr_y;
	int  pixel_wall;

	angle = modulo_pi(angle);

	incr_x = TILE_SIZE;
	incr_y = incr_x * tan(angle);

	x_inter_coord = floor(temp->player->p_x / TILE_SIZE) * TILE_SIZE;
	pixel_wall = inter_wall_check(angle, &x_inter_coord, &incr_x, 1);
	y_inter_coord = temp->player->p_y +  (x_inter_coord - temp->player->p_x) * tan(angle);
	incr_y *= check_direction(incr_y, angle, 1); //! ICI

	while (walled(x_inter_coord - pixel_wall, y_inter_coord, temp, 'V'))
	{
		if (temp->ray->cast == 1350)
		{
			printf(" ---->>>CAST  = %d - %c\n", temp->ray->cast, 'V'); //! ICI 1350 NEGATIF
			printf(" --- incr_Y  = %f\n", incr_y);
			printf("x_inter = %f\ny_inter = %f\n\n", x_inter_coord, y_inter_coord);

		}
		x_inter_coord += incr_x;
		y_inter_coord += incr_y;
		if (temp->ray->cast == 1350)
		{
			printf("CAST  = %d - %c\n", temp->ray->cast, 'V'); //! ICI 1350 NEGATIF
			printf(" --- incr_Y  = %f\n", incr_y);
			printf("x_inter = %f\ny_inter = %f\n\n", x_inter_coord, y_inter_coord);

		}
	}

	return (sqrt(pow(x_inter_coord - temp->player->p_x, 2) + pow(y_inter_coord - temp->player->p_y, 2)));
}


int	walled(float x, float y, t_data *data, char c)
{
	int x_pos;
	int y_pos;

	y -= 1;
	x_pos = floor(x / TILE_SIZE);
	y_pos = floor(y / TILE_SIZE);

	if (x < 0 || y < 0)
		return 0;
	if (y_pos >= data->map->map_h || x_pos >= data->map->map_w)
		return 0;

	if (data->map->map[y_pos] && x_pos <= ft_strlen(data->map->map[y_pos]))
	{
		if (data->map->map[y_pos][x_pos] == '1')
		{
			if((data->ray->cast == 1350))
			{
				printf(" ---- WALLED ---- %c --\n", c);
				printf("=================================================================\n\n");
			}

//		printf("--- %c - %d - %d - %d ---\n",c ,data->ray->cast, x_pos, y_pos);
			return 0;
		}

	}
	return 1; //$ OK
}

int	inter_wall_check(float angle, float *inter,float *incr, int i) //$ ajuste le signe de l incr + TILE_SIZE + Pixel
{
	if (i == 0)
	{
		if (angle >= 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*incr *= -1;
	}
	else if (i == 1)
	{
		if (!(angle >= M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*incr *= -1;
	}
	return (1); //$ OK
}

int	check_direction(float incr, float angle, int i) // $ ajuste la direction de l increment
{
	if (i == 0)
	{
		if((angle > (M_PI / 2) && angle < (3 * M_PI) / 2) && incr > 0)
			return (-1);
		else if(!(angle > (M_PI / 2) && angle < (3 * M_PI) / 2) && incr < 0)
			return(-1);
	}
	else if (i == 1)
	{
		if(angle > 0 && angle < M_PI && incr < 0)
			return (-1);
		else if(!(angle > 0 && angle < M_PI) && incr > 0)
			return (-1);
	}
	return 1;
}

