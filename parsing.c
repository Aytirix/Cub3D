/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:30:07 by hle-roux          #+#    #+#             */
/*   Updated: 2024/08/28 15:31:03 by hle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "so_long.h"

// Parsing de so_long
// va etre utile car meme forme de map

int	map_checker(char **map)
{
	int	i;

	i = 0;
	intrusion_checker(map);
	wall_checker(map, map_lenth(map), map_height(map));
	format_checker(map);
	if (element_checker(map, 'P') != 1)
		ft_error(1);
	if (element_checker(map, 'C') < 1)
		ft_error(1);
	if (element_checker(map, 'E') != 1)
		ft_error(1);
	return (0);
}

int	wall_checker(char **map, int l, int h)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < l)
	{
		if (map[0][j] != '1')
			ft_error(1);
		j++;
	}
	while (++i < h - 1)
	{
		if (map[i][0] != '1' || map[i][l - 1] != '1')
			ft_error(1);
	}
	j = 0;
	while (j < l)
	{
		if (map[h - 1][j] != '1')
			ft_error(1);
		j++;
	}
	return (0);
}

int	element_checker(char **map, char p)
{
	int	i;
	int	j;
	int	n;

	n = 0;
	j = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == p)
				n++;
			j++;
		}
		i++;
	}
	return (n);
}

int	intrusion_checker(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j + 1])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'P'
				&& map[i][j] != 'C' && map[i][j] != 'E')
				ft_error(1);
			j++;
		}
		i++;
	}
	return (0);
}
