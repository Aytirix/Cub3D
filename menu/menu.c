/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:43:41 by thmouty           #+#    #+#             */
/*   Updated: 2024/10/11 20:22:42 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*convert_key_to_string(int key)
{
	if (key == 0)
		return (ft_strdup("NOT ASSIGNED"));
	if (key == 65307)
		return (ft_strdup("ESC"));
	if (key == 65362)
		return (ft_strdup("UP"));
	if (key == 65364)
		return (ft_strdup("DOWN"));
	if (key == 65361)
		return (ft_strdup("LEFT"));
	if (key == 65363)
		return (ft_strdup("RIGHT"));
	if (key == 61)
		return (ft_strdup("+"));
	if (key == 45)
		return (ft_strdup("-"));
	if (key == 65289)
		return (ft_strdup("TAB"));
	return (ft_strdup((char []){key, 0}));
}

static void	background_black(t_data *data)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			color = data->buffer[i * WIDTH + j];
			data->buffer[i * WIDTH + j] = (((color >> 18) & 0x3F) << 16)
				| (((color >> 10) & 0x3F) << 8) | ((color >> 2) & 0x3F);
			j++;
		}
		i++;
	}
}

void	check_update_lisent(t_data *data, int new)
{
	int			x;
	int			y;
	t_settings	*tmp;
	t_settings	*tmp2;

	tmp2 = data->settings->forward;
	tmp = data->settings->forward;
	mlx_mouse_get_pos(data->mlx, data->mlx_win, &x, &y);
	while (tmp)
	{
		if (x > tmp->x && x < tmp->x + 135 && y > tmp->y && y < tmp->y + 25)
		{
			while (tmp2)
			{
				if (tmp2->key == new)
					tmp2->key = 0;
				tmp2 = tmp2->next;
			}
			tmp->key = new;
			return ;
		}
		tmp = tmp->next;
	}
}

static void	add_settings(t_data *data, char *key, t_settings *setting)
{
	char		*tmp;
	static int	i = WIDTH / 2.14;
	static int	j = HEIGHT / 10;

	if (!key)
	{
		i = WIDTH / 2.14;
		j = HEIGHT / 10;
		return ;
	}
	mlx_string_put(data->mlx, data->mlx_win, i, j, 0x00FF00, key);
	tmp = convert_key_to_string(setting->key);
	mlx_string_put(data->mlx, data->mlx_win, i + 100, j, 0x00FF00, tmp);
	mlx_string_put(data->mlx, data->mlx_win, i, j + 20, 0x00FF00,
		"---------------------");
	setting->x = i - 10;
	setting->y = j - 20;
	j += 50;
	free(tmp);
}

void	draw_menu(t_data *data)
{
	background_black(data);
	add_settings(data, "Avancer", data->settings->forward);
	add_settings(data, "Reculer", data->settings->backward);
	add_settings(data, "Gauche", data->settings->left);
	add_settings(data, "Droite", data->settings->right);
	add_settings(data, "Zoom +", data->settings->zoom_in);
	add_settings(data, "Zoom -", data->settings->zoom_out);
	add_settings(data, "Zoom", data->settings->big_zoom);
	add_settings(data, NULL, NULL);
}
