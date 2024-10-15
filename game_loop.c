/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:43:41 by hle-roux          #+#    #+#             */
/*   Updated: 2024/10/15 17:55:36 by hle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

#include <time.h>

//$ DEVNOTES

//* RAYCASTING		OK (1 bug)
//* OPTIMISATION 	OK
//* TEXTURES		TODO <<--
//* MOUVEMENTS		DOING

int	game_loop(void *temp) // delete img - check pos - cast ray - update image
{
	t_data *data;
	data = temp;

	if(data->img_ptr)
		mlx_destroy_image(data->mlx, data->img_ptr);

	data->img_ptr =  mlx_new_image(data->mlx, 1900, 1080);
	data->buffer = (int *)mlx_get_data_addr(data->img_ptr, &data->bpp, &data->size_l, &data->endian);
	ray_casting(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_ptr, 0,0);
		printf("----------------\n");

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

		if (cast == 1485)
		{	printf("CAST : %d\n",cast);
			printf("vertical : %f\n",vertical_wall);
			printf("horizontal : %f\n\n",horizontal_wall);
		}
		if (vertical_wall < horizontal_wall)
			temp->ray->wall_dist = vertical_wall;
		else
			temp->ray->wall_dist = horizontal_wall;

		render(temp, cast);
		cast++;
		temp->ray->ray_angle += (temp->player->fov_rad / 1900);

	}



}

float	horizontal(t_data *temp, float angle)
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
	pixel_wall = inter_wall_check(angle, &y_inter_coord, &incr_y, 0);
	x_inter_coord = temp->player->p_x +  (y_inter_coord - temp->player->p_y) / tan(angle);
	incr_x *= check_direction(incr_x, angle, 0);

	while (walled(x_inter_coord, y_inter_coord - pixel_wall, temp))
	{
		x_inter_coord += incr_x;
		y_inter_coord += incr_y;
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
	incr_y *= check_direction(incr_y, angle, 1);

	if (temp->ray->cast == 1485)
	{
		printf("=======\n");
		printf("x inter : %f \n", x_inter_coord);
		printf("y inter : %f \n", y_inter_coord);
		printf("=======\n\n");
	}
	while (walled(x_inter_coord - pixel_wall, y_inter_coord, temp))
	{
		x_inter_coord += incr_x;
		y_inter_coord += incr_y;
	}
	if (temp->ray->cast == 1485 )
	{
	printf("x_wall : %f\n", x_inter_coord);
	printf("y_wall : %f\n\n", y_inter_coord);
	}
	return (sqrt(pow(x_inter_coord - temp->player->p_x, 2) + pow(y_inter_coord - temp->player->p_y, 2)));
}


int	walled(float x, float y, t_data *data)
{
	int x_pos;
	int y_pos;

	y -= 1;
	x_pos = floor(x / TILE_SIZE);
	y_pos = floor(y / TILE_SIZE);
	if (data->ray->cast == 1485)
		printf("p_x | p_y : %d || %d\n", x_pos, y_pos);

	if (x < 0 || y < 0)
		return 0;
	if (y_pos >= data->map->map_h || x_pos >= data->map->map_w)
		return 0;

	if (data->map->map[y_pos] && x_pos <= ft_strlen(data->map->map[y_pos]))
	{
		if (data->map->map[y_pos][x_pos] == '1')
			return 0;
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

