/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:51:03 by hle-roux          #+#    #+#             */
/*   Updated: 2024/09/04 15:34:20 by hle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_fprintf(2, "Error\nWrong number of arguments (only 1 required))\n");
		return (1);
	}
	init_data(&data, argv[1]);
	game_launch(&data);
	free_all_stop(&data, 0);
	return (0);
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
}

t_data	*init_data(t_data *data, char *file_name)
{
	data->ray = calloc(1, sizeof(t_ray));
	data->map = calloc(1, sizeof(t_map));
	data->player = calloc(1, sizeof(t_player));
	data->img_ptr = NULL;
	data->map->img_no = NULL;
	data->map->img_so = NULL;
	data->map->img_we = NULL;
	data->map->img_ea = NULL;
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

void	game_launch(t_data *data)
{
	create_window(data);
}

void	create_window(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Hello world!");
	if (data->mlx == 0 || data->mlx_win == 0)
	{
		printf("ended\n");
		return ;
	}
	printf("map_h %d \n\n\n", data->map->map_h);
	mlx_mouse_move(data->mlx, data->mlx_win, WIDTH / 2, HEIGHT / 2);
	mlx_loop_hook(data->mlx, &game_loop, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, &key_press, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, &key_release, data);
	mlx_mouse_hide(data->mlx, data->mlx_win);
	mlx_loop(data->mlx);
	printf("-- END -- \n");
}

// --------------	Cub3d	--------------------------

// -> 4 parties
//		- Map + Window 		= mlx + parsing
//		- Raycasting 		= Maths, calculation
//		- Rendering 		= Image + scaling
//		- Player Mov		= mlx

//	Diviser en rayon vertical puis placer le wall puis le floor ceilling

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
//		- For each rays,
// calculate the dist to wall(with horiz and vertical inter)
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

// Mov handeling + rendering = get_keys and adjust pos + cam_plan +	rotation

// 			---		RESSOURCES	---
//
//	https://medium.com/@afatir.ahmedfatir/cub3d-tutorial-af5dd31d2fcf#:~:text=some%20walls%20now.-,Part%203%3A%20Rendering%3A,-so%20now%20we
//	https://github.com/AhmedFatir/cub3D

//	https://reactive.so/post/42-a-comprehensive-guide-to-cub3d/
//	https://medium.com/@rtailidounia/raycasting-in-cub3d-42-network-project-a-practical-tutorial-using-vectors-68eeb16b3de2

//	https://github.com/iciamyplant/Cub3d-Linux
