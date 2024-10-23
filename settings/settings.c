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
	settings->forward->key = 65362;
	settings->forward->press = 0;
	settings->forward->next = settings->backward;
	settings->backward->key = 65364;
	settings->backward->press = 0;
	settings->backward->next = settings->left;
	settings->left->key = 65361;
	settings->left->press = 0;
	settings->left->next = settings->right;
	settings->right->key = 65363;
	settings->right->press = 0;
	settings->right->next = settings->menu;
	return (init_lsettings_2(settings));
}

t_lsettings	*init_lsettings_2(t_lsettings *settings)
{
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
	settings->big_zoom->next = NULL;
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
