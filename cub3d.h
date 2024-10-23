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

# define PLAYER_SPEED 1
# define MOVE_SPEED 0.0010
# define FOV 60
# define TILE_SIZE 300
# define EPSILON 0.000001
# define WIDTH 1900
# define HEIGHT 1080
# define COL_WALL 10

# define BOLD_RED "\033[1;31m"
# define RESET "\033[0m"

// ------------------ STRUCTURE -------------------------

typedef struct s_texture
{
	char				*name;
	void				*img_ptr;
	char				*txtr_ptr;
	int					width;
	int					height;
	int					bpp;
	int					size_line;
	int					endian;

}						t_texture;

typedef struct s_ray
{
	double				wall_dist;
	double				wall_dist_f;
	double				wall_dist_b;
	double				wall_dist_l;
	double				wall_dist_r;
	int					color_flag;
	int					side;
	int					x_ray;
	float				ray_angle;
	int					cast;
	int					is_horizontal;
	double				h_x;
	double				v_y;
}						t_ray;

typedef struct s_player
{
	double				p_speed;
	double				p_x;
	double				p_y;
	double				angle;
	float				fov_rad;
	int					rota_flag;

}						t_player;

typedef struct s_map
{
	char				**map;
	t_texture			*img_no;
	t_texture			*img_so;
	t_texture			*img_we;
	t_texture			*img_ea;
	int					floor_color;
	int					ceilling_color;
	int					p_x_location;
	int					p_y_location;
	int					map_h;
	int					map_w;
}						t_map;

typedef struct s_settings
{
	int					key;
	int					press;
	int					x;
	int					y;
	struct s_settings	*next;
}						t_settings;

typedef struct s_lsettings
{
	t_settings			*forward;
	t_settings			*backward;
	t_settings			*left;
	t_settings			*right;
	t_settings			*menu;
	t_settings			*zoom_in;
	t_settings			*zoom_out;
	t_settings			*big_zoom;
}						t_lsettings;

typedef struct s_data
{
	void				*mlx;
	void				*mlx_win;
	void				*img_ptr;
	int					*buffer;
	int					size_l;
	int					bpp;
	int					endian;
	t_map				*map;
	t_ray				*ray;
	t_player			*player;
	struct s_lsettings	*settings;
}						t_data;

// ------------------ INITIALISATION -------------------------

t_data					*init_data(t_data *data, char *file_name);
void					get_start_angle(t_data *data, char c);
void					create_window(t_data *data);

// ------------------ FONCTIONS -------------------------

int						game_loop(t_data *data);
void					ray_casting(t_data *temp);
float					vertical(t_data *temp, float angle);
float					horizontal(t_data *temp, float angle);
float					modulo_pi(float x);
int						inter_wall_check(float angle, float *inter, float *incr,
							int i);
int						walled(float x, float y, t_data *data);
void					calcul_rayon_hv(t_data *data, float modulo,
							double *var);
void					draw_square(t_data *data, double x, int y, int color);

// ------------------ SETTINGS -------------------------

t_lsettings				*init_lsettings(void);
t_lsettings				*init_lsettings_2(t_lsettings *settings);
t_lsettings				*free_settings(t_lsettings *settings);

// ------------------ MENU -------------------------

void					draw_menu(t_data *data);
void					check_update_lisent(t_data *data, int new);

// ------------------ UTILS -------------------------

int						check_direction(float incr_x, float angle, int i);
void					free_all_stop(t_data *data, int code);

// ------------------ MOVEMENT -------------------------

int						mouse_move_hook(t_data *data);
int						key_press(int key, t_data *data);
int						key_press_2(int key, t_data *data);
int						key_release(int key, t_data *data);
int						key_hook(t_data *data);
void					forward(t_data *data);
void					backward(t_data *data);
void					right(t_data *data);
void					left(t_data *data);

// ------------------ TEXTURE -------------------------

void					load_textures(t_data *data);
t_texture				*get_side_texture(t_data *data);
void					texture_to_wall(t_data *data, int wall_bottom,
							int wall_top, int wall_size);
float					calcul_x_offset(t_data *data, t_texture *txtr);
float					calcul_y_offset(int wall_top, int wall_size,
							float increment);

// ------------------ RENDERING -------------------------

void					render(t_data *data, int cast);
void					put_ceiling(t_data *data, int x, int y, int color);
void					put_floor(t_data *data, int x, int y, int color);
void					put_pixel(t_data *data, int x, int y, int color);

// ------------------ PARSING -------------------------
void					parsing(t_data *data, char *file);
int						parsing_map(t_data *data, int fd, int i);
int						search_rgb(int *rgb, int fd, char *direction, int *err);
int						check_name_cub(t_data *data, char *name);

// ------------------  -------------------------

#endif
