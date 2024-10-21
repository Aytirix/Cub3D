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

static void background_black(t_data *data)
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
			data->buffer[i * WIDTH + j] = (((color >> 18) & 0x3F) << 16) | (((color >> 10) & 0x3F) << 8) | ((color >> 2) & 0x3F);
			j++;
		}
		i++;
	}
}

void add_settings(t_data *data, char *key, char *value)
{
	
}

void	draw_menu(t_data *data)
{
	background_black(data);
}
