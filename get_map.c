/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 09:13:49 by hle-roux          #+#    #+#             */
/*   Updated: 2024/08/29 15:14:21 by hle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Vient de so_long
// Pareil va etre utile pour recuperer la map du .cub

#include"cub3d.h"


char	**get_map(char *map_name)
{
	int		i;
	int		fd;
	char	**map;

	i = 0;
	map = malloc((sizeof(char *) * (13 + 1)));
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		ft_error("Map impossible to read \n");
	while (1)
	{
		map[i] = get_next_line(fd);
		if (map[i] == NULL)
			break ;
		i++;
	}
	map[i] = NULL;
	return (map);
}

int	format_checker(char **map)
{
	int		y;
	int		x;
	int		columns;

	x = 0;
	y = 0;
	columns = 0;
	while (map[0][columns] != 0)
		columns++;
	while (map[y] != NULL)
	{
		while (map[y][x])
			x++;
		if (x != columns)
		{
			ft_error("Wrong format \n");
			return (0);
		}
		x = 0;
		y++;
	}
	return (1);
}

int	map_lenth(char **map)
{
	int	i;

	i = 0;
	while (map[0][i])
		i++;
	return (i - 1);
}

int	map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
