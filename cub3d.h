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

# include ".mlx/mlx.h"
# include "Libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# define FOV 70
# define TILE_SIZE 30 // taille des tiles, arbitraire ?
# define EPSILON 0.000001
# define WIDTH 1900
# define HEIGHT 1080

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define BOLD_RED "\033[1;31m"
# define RESET "\033[0m"

// ------------------ STRUCTURE -------------------------

typedef struct s_ray
{
	double		wall_dist;
	int			color_flag;

	int side; // 0 si c'est un cote x qui est touche (vertical), 1 si un cote y (horizontal)

	int lineheight; // hauteur de la ligne a dessiner
	int drawstart;  // position de debut ou il faut dessiner
	int drawend;    // position de fin ou il faut dessiner

	int			x_ray;
	float		ray_angle;
	int			cast;
}				t_ray;

typedef struct s_player
{
	int			p_x;
	int			p_y;

	double		angle;
	float		fov_rad;

	int			rota_flag;

}				t_player;

typedef struct s_map
{
	char **map; // init

	int mapx; // coordonée x du carré dans lequel est pos
	int mapy; // coordonnée y du carré dans lequel est pos ????

	// Images
	char		*img_NO;
	char		*img_SO;
	char		*img_WE;
	char		*img_EA;

	// Couleurs du sol et du plafond
	int			floor_color;
	int			ceilling_color;

	int			p_x_location;
	int			p_y_location;

	int map_h; // init
	int map_w; // init

}				t_map;

typedef struct s_data
{
	void *mlx;     // init
	void *mlx_win; // init
	void		*img_ptr;
	int			*buffer;

	int			size_l;
	int			bpp;
	int			endian;
	int			keys[4];
	t_map		*map;
	t_ray		*ray;
	t_player	*player;

}				t_data;

// ------------------ INITIALISATION -------------------------

void			game_launch(t_data *data);
t_data			*init_data(t_data *data, char *map_name);
void			get_ply_pos(t_data *data);
void			get_start_angle(t_data *data, char c);

// ------------------ FONTIONS -------------------------

int				game_loop(void *temp);
void			ray_casting(t_data *temp);
float			vertical(t_data *temp, float angle);
float			horizontal(t_data *temp, float angle);
float			modulo_pi(float x);
int				inter_wall_check(float angle, float *inter, float *incr, int i);
int				walled(float x, float y, t_data *data);

// ------------------ UTILS -------------------------

int				check_direction(float incr_x, float angle, int i);
void			free_all_stop(t_data *data, int code);

// ------------------ MOVEMENT -------------------------

int				mouse_move_hook(t_data *data);
int				key_press(int key, t_data *data);
int				key_release(int key, t_data *data);
int				key_hook(t_data *data);
void			forward(t_data *data);
void			backward(t_data *data);
void			right(t_data *data);
void			left(t_data *data);

// ------------------ RENDERING -------------------------

void			render(t_data *data, int cast);
void			put_ceiling(t_data *data, int x, int y, int color);
void			put_floor(t_data *data, int x, int y, int color);
void			put_pixel(t_data *data, int x, int y, int color);

void			create_window(t_data *data);

// ------------------ PARSING -------------------------
void			parsing(t_data *data, char *file);
int				parsing_map(t_data *data, int fd, int i);
int				search_rgb(int *rgb, int fd, char *direction, int *err);

// ------------------  -------------------------

#endif
