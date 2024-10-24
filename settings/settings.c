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

t_lsettings	*init_lsettings(void)
{
	t_lsettings	*settings;

	settings = ft_calloc(1, sizeof(t_lsettings));
	settings->forward = ft_calloc(1, sizeof(t_settings));
	settings->backward = ft_calloc(1, sizeof(t_settings));
	settings->left = ft_calloc(1, sizeof(t_settings));
	settings->right = ft_calloc(1, sizeof(t_settings));
	settings->menu = ft_calloc(1, sizeof(t_settings));
	settings->zoom_in = ft_calloc(1, sizeof(t_settings));
	settings->zoom_out = ft_calloc(1, sizeof(t_settings));
	settings->big_zoom = ft_calloc(1, sizeof(t_settings));
	settings->rot_left = ft_calloc(1, sizeof(t_settings));
	settings->rot_right = ft_calloc(1, sizeof(t_settings));
	settings->forward->key = 119;
	settings->forward->press = 0;
	settings->forward->next = settings->backward;
	settings->backward->key = 115;
	settings->backward->press = 0;
	settings->backward->next = settings->left;
	settings->left->key = 97;
	settings->left->press = 0;
	settings->left->next = settings->right;
	return (init_lsettings_2(settings));
}

t_lsettings	*init_lsettings_2(t_lsettings *settings)
{
	settings->right->key = 100;
	settings->right->press = 0;
	settings->right->next = settings->menu;
	settings->menu->key = 65470;
	settings->menu->press = 0;
	settings->menu->next = settings->zoom_in;
	settings->zoom_in->key = 61;
	settings->zoom_in->press = 0;
	settings->zoom_in->next = settings->zoom_out;
	settings->zoom_out->key = 45;
	settings->zoom_out->press = 0;
	settings->zoom_out->next = settings->big_zoom;
	settings->big_zoom->key = 65289;
	settings->big_zoom->press = 5;
	settings->big_zoom->next = settings->rot_left;
	settings->rot_left->key = 65361;
	settings->rot_left->press = 0;
	settings->rot_left->next = settings->rot_right;
	settings->rot_right->key = 65363;
	settings->rot_right->press = 0;
	settings->rot_right->next = NULL;
	return (settings);
}

t_lsettings	*free_settings(t_lsettings *settings)
{
	t_settings	*tmp;

	while (settings->forward)
	{
		tmp = settings->forward;
		settings->forward = settings->forward->next;
		free(tmp);
	}
	free(settings);
	return (NULL);
}
