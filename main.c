/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:51:03 by hle-roux          #+#    #+#             */
/*   Updated: 2024/10/21 14:43:28 by hle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

int main(int argc, char** argv)
{
	t_data data;

	if (argc != 2)
		return 0;

	init_data(&data, argv[1]);

	game_launch(&data);
	free_all_stop(&data, 0);
	return (0);
}

t_data*	init_data(t_data *data, char *file_name)
{
	data->ray = calloc(1, sizeof(t_ray));
	data->map = calloc(1, sizeof(t_map));
	data->map->img_EA = calloc(1,sizeof(t_texture));
	data->map->img_NO = calloc(1,sizeof(t_texture));
	data->map->img_WE = calloc(1,sizeof(t_texture));
	data->map->img_SO = calloc(1,sizeof(t_texture));
	data->player = calloc(1, sizeof(t_player));
	data->img_ptr = NULL;
	data->map->img_SO->name = NULL;
	data->map->img_WE->name = NULL;
	data->map->img_EA->name = NULL;
	data->map->map = NULL;
	data->map->map_h = 0;
	data->map->map_w = 0;
	data->map->floor_color = 0;
	data->map->ceilling_color = 0;
	data->keys[0] = 0;
	data->keys[1] = 0;
	data->keys[2] = 0;
	data->keys[3] = 0;
	parsing(data, file_name);
	return (data);
}

void	load_textures(t_data *data)
{
	printf("dir : %s\n", data->map->img_NO->name);
	data->map->img_NO->img_ptr = mlx_xpm_file_to_image(data->mlx, \
		data->map->img_NO->name, &data->map->img_NO->width, \
		&data->map->img_NO->height);

	data->map->img_NO->txtr_ptr = mlx_get_data_addr(data->map->img_NO->img_ptr, &data->map->img_NO->bpp, &data->map->img_NO->size_line, &data->map->img_NO->endian);



}

void	game_launch(t_data *data)
{
	create_window(data);
}




// --------------	Cub3d	--------------------------

// -> 4 parties
//		- Map + Window 		= mlx + parsing
//		- Raycasting 		= Maths, calculation
//		- Rendering 		= Image + scaling
//		- Player Mov		= mlx

//	Principe = Diviser en rayon vertical puis placer le wall puis le floor / ceilling


//	---------------- PROCESS -------------------

// 	- Init Struct		--> Some may ne missing but will see
//	- Init Data 		--> almost done
//	- Create game loop	--> ok for now
//	- Init window		--> OK ?
//	- Start raycasting
//	- Render Wall
//	- Handle mvt

//	----------------RAYCASTING -------------------

// 1/ Find 1st ray = (FOV)
// 2/ Loop and increment
// 3/ Horizontal crossing
// 4/ Vertical crossing
// 5/ Get Wall Dist
// 6/ Rendering mlx


// STEPS =
//		- get FOV and pos
//		- Cut in rays
//		- For each rays, calculate the dist to wall (with horiz and vertical inter)
//		- Render walls, w/ thales and mlx

// 1 FOV = x rays
// 1 rays = 1 Wall distance
// 1 wall distance = 1 wall height
// 1 wall height = render wall + floor + ceilling


//	----------------RENDERING -------------------

//	Boucler pour chaque rayon (tranches)
//	Fix fisheye + get Wall Height
//	Calculate bottom and top pixel
//	Draw colors


//	----------------OTHER -------------------

// Movement handeling + rendering = get_keys and adjust pos + cam_plan + rotation



// 			---	 RESSOURCES	---
//
//	https://medium.com/@afatir.ahmedfatir/cub3d-tutorial-af5dd31d2fcf#:~:text=some%20walls%20now.-,Part%203%3A%20Rendering%3A,-so%20now%20we
//	https://github.com/AhmedFatir/cub3D

//	https://reactive.so/post/42-a-comprehensive-guide-to-cub3d/
//	https://medium.com/@rtailidounia/raycasting-in-cub3d-42-network-project-a-practical-tutorial-using-vectors-68eeb16b3de2

//	https://github.com/iciamyplant/Cub3d-Linux
