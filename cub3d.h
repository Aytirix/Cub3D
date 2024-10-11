/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:56:08 by hle-roux          #+#    #+#             */
/*   Updated: 2024/10/11 20:12:09 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <math.h>

# include"gnl/get_next_line.h"
# include"mlx/mlx.h"
# include"ft_printf/libftprintf.h"


# define FOV 60
# define TILE_SIZE 30 // taille des tiles, arbitraire ?
# define EPSILON 0.000001

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif


// ------------------ STRUCTURE -------------------------

typedef struct	s_ray
{
	double	wall_dist;
	int		color_flag;

	int		side; // 0 si c'est un cote x qui est touche (vertical), 1 si un cote y (horizontal)

	int		lineheight; //hauteur de la ligne a dessiner
	int		drawstart; //position de debut ou il faut dessiner
	int		drawend; //position de fin ou il faut dessiner

	int		x_ray;
	float	ray_angle;
	int		cast;
}	t_ray;

typedef struct s_player
{
	int		p_x;
	int		p_y;

	double	angle;
	float	fov_rad;

	int		rota_flag;

}	t_player;


typedef struct s_map
{
	char**	map; // init

	int		mapx; // coordonée x du carré dans lequel est pos
	int		mapy; // coordonnée y du carré dans lequel est pos ????

	int		p_x_location;
	int		p_y_location;

	int		map_h; // init
	int		map_w; // init

}	t_map;

typedef struct s_data
{
	void		*mlx;		//init
	void		*mlx_win;	//init
	void		*img_ptr;
	int			*buffer;

	int			size_l;
	int			bpp;
	int			endian;

	t_map		*map;
	t_ray		*ray;
	t_player	*player;

}	t_data;


// ------------------ INITIALISATION -------------------------

void	game_launch();
t_data*	init_data(t_data *data, char *map_name);
void	get_ply_pos(t_data *data);
void	get_start_angle(t_data *data, char c);

// ------------------ FONTIONS -------------------------

int		game_loop();
void	ray_casting(t_data *temp);
float	vertical(t_data *temp, float angle);
float	horizontal(t_data *temp, float angle);
float	modulo_pi(float x);
int		inter_wall_check(float angle, float *inter,float *incr, int i);
int		walled(float x, float y, t_data *data);


// ------------------ UTILS -------------------------

int	ft_close(t_data *data);
void	clear_img(t_data *data);
int	check_direction(float incr_x, float angle, int i);
void free_all_stop(t_data *data, int code);




// ------------------ MOVEMENT -------------------------

int	key_hook(int key, t_data *data);
void forward(t_data *data);
void backward(t_data *data);
void right(t_data *data);
void left(t_data *data);




// ------------------ RENDERING -------------------------

void	render(t_data *data, int cast);
void	put_ceiling(t_data *data, int x, int y, int color);
void	put_floor(t_data *data, int x, int y, int color);
void	put_pixel(t_data *data, int x, int y, int color);


// ------------------ MAP -------------------------

char	**get_map(char *map_name);
//int	format_checker(char **map);
//int	map_lenth(char **map);
//int	map_height(char **map);

void	create_window();


void	ft_error(char* message);


// ------------------  -------------------------


#endif
