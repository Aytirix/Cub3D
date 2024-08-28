/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:51:03 by hle-roux          #+#    #+#             */
/*   Updated: 2024/08/28 18:32:55 by hle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int main()
{


	return 0;
}



// --------------	Cub3d	--------------------------

// 			---	 RESSOURCES	---
//
//	https://medium.com/@afatir.ahmedfatir/cub3d-tutorial-af5dd31d2fcf#:~:text=some%20walls%20now.-,Part%203%3A%20Rendering%3A,-so%20now%20we
//	https://reactive.so/post/42-a-comprehensive-guide-to-cub3d/
//	https://medium.com/@rtailidounia/raycasting-in-cub3d-42-network-project-a-practical-tutorial-using-vectors-68eeb16b3de2
//	https://www.youtube.com/watch?v=js7HW65MmNw&list=PL0H9-oZl_QOHM34HvD3DiGmwmj5X7GvTW
//	https://github.com/iciamyplant/Cub3d-Linux


// -> 4 parties
//		- Map + Window 		= mlx + parsing
//		- Raycasting 		= Maths, calculation
//		- Rendering 		= Image + scaling
//		- Player Mov		= mlx

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
