/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:51:03 by hle-roux          #+#    #+#             */
/*   Updated: 2024/08/31 17:12:54 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

int main(int argc, char** argv)
{
	ft_printf("argc = %d\n", argc);

	get_map(argv[1]);

	create_window();

	return 0;
}



// --------------	Cub3d	--------------------------

// 			---	 RESSOURCES	---
//
//	https://medium.com/@afatir.ahmedfatir/cub3d-tutorial-af5dd31d2fcf#:~:text=some%20walls%20now.-,Part%203%3A%20Rendering%3A,-so%20now%20we
//	https://github.com/AhmedFatir/cub3D

//	https://reactive.so/post/42-a-comprehensive-guide-to-cub3d/
//	https://medium.com/@rtailidounia/raycasting-in-cub3d-42-network-project-a-practical-tutorial-using-vectors-68eeb16b3de2

//	https://github.com/iciamyplant/Cub3d-Linux


// -> 4 parties
//		- Map + Window 		= mlx + parsing
//		- Raycasting 		= Maths, calculation
//		- Rendering 		= Image + scaling
//		- Player Mov		= mlx

//	Principe = Diviser en rayon vertical puis placer le wall puis le floor / ceilling 

//	----------------COMPILATION -------------------

// When compiling the code, you must include the necessary frameworks
// 	and link the glfw library, as well as the libmlx.a.
// The flag (-O3 -ffast-math) is used for optimization.
// The flag (-framework) is used to specify the required frameworks.
// the flag (-lglfw) is for linking the glfw library
// the flag (-L) is for the path to the glfw library
// the flag (-o) is for the name of the executable file

//	----------------COMPILATION -------------------

// Creer des structures pour player, rayon, data, mlx.. etc


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
