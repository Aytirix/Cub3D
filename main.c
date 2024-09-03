/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:51:03 by hle-roux          #+#    #+#             */
/*   Updated: 2024/09/03 18:53:07 by hle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

int main(int argc, char** argv)
{
	t_data *data;

	if (argc != 2)
		return 0;

	data = calloc(1, sizeof(t_data));

	init_data(data, argv[1]);

	game_launch(data);

	return 0;
}

t_data*	init_data(t_data *data, char *map_name)
{
	data->ray = calloc(1, sizeof(t_ray));
	data->map = calloc(1, sizeof(t_map));
	data->player = calloc(1, sizeof(t_player));
	data->map->map = get_map(map_name);
	get_ply_pos(data);

	return (data);
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
//	- Create game loop
//	- Init window
//	- Start raycasting

//	----------------RAYCASTING -------------------

// 1/ Find 1st ray = (FOV)
// 2/ Loop and increment
// 3/ Horizontal crossing
// 4/ Vertical crossing
// 5/ Affichage mlx


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
