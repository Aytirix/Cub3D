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
		ft_fprintf(2, "Error\nWrong number of arguments (only 1 required)\n");
		return (1);
	}
	init_data(&data, argv[1]);
	create_window(&data);
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
	data->player->p_speed = PLAYER_SPEED * TILE_SIZE / 6;
	data->player->fov_rad = (FOV * M_PI) / 180;
}

t_data	*init_data(t_data *data, char *file_name)
{
	data->ray = ft_calloc(1, sizeof(t_ray));
	data->map = ft_calloc(1, sizeof(t_map));
	data->player = ft_calloc(1, sizeof(t_player));
	data->map->img_no = calloc(1, sizeof(t_texture));
	data->map->img_so = calloc(1, sizeof(t_texture));
	data->map->img_ea = calloc(1, sizeof(t_texture));
	data->map->img_we = calloc(1, sizeof(t_texture));
	data->map->img_no->name = NULL;
	data->map->img_so->name = NULL;
	data->map->img_we->name = NULL;
	data->map->img_ea->name = NULL;
	data->map->img_no->img_ptr = NULL;
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->img_ptr = NULL;
	data->map->map = NULL;
	data->map->map_h = 0;
	data->map->map_w = 0;
	data->map->floor_color = 0;
	data->map->ceilling_color = 0;
	data->settings = init_lsettings();
	parsing(data, file_name);
	return (data);
}

static int	close_window(t_data *data)
{
	free_all_stop(data, 0);
	return (0);
}

void	create_window(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Hello world!");
	if (data->mlx == 0 || data->mlx_win == 0)
		return ;
	load_textures(data);
	mlx_mouse_move(data->mlx, data->mlx_win, WIDTH / 2, HEIGHT / 2);
	mlx_hook(data->mlx_win, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx, &game_loop, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, &key_press, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, &key_release, data);
	mlx_mouse_hide(data->mlx, data->mlx_win);
	mlx_loop(data->mlx);
}
