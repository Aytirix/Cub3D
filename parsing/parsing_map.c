/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:04:20 by hle-roux          #+#    #+#             */
/*   Updated: 2024/09/21 09:28:42 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	get_player_position(t_data *data, char c, int i, int j)
{
	static int	player = 0;

	if (i == -1 && player == 0)
	{
		ft_fprintf(2, "Error\n%sNo player position%s\n", BOLD_RED, RESET);
		free_all_stop(data, 1);
	}
	if (i == -1)
		return ;
	if (ft_strchr("NSEW", c))
	{
		if (player)
		{
			ft_fprintf(2, "Error\n%sMultiple player position%s\n", BOLD_RED,
				RESET);
			free_all_stop(data, 1);
		}
		player = 1;
		data->map->p_x_location = j + 1;
		data->map->p_y_location = i + 1;
		data->player->p_x = (j) * TILE_SIZE + TILE_SIZE / 2;
		data->player->p_y = (i) * TILE_SIZE + TILE_SIZE / 2;
		get_start_angle(data, data->map->map[i][j]);
	}
}

static void	check_flood_fill(t_data *data, int y, int x, char replace)
{
	if (y < 0 || x < 0 || y >= data->map->map_h || x >= data->map->map_w)
	{
		ft_fprintf(2, "Error\n%sMap not closed or space found%s\n", BOLD_RED,
			RESET);
		free_all_stop(data, 1);
	}
	if (data->map->map[y] && data->map->map[y][x]
		&& (data->map->map[y][x] == '1' || data->map->map[y][x] == replace))
		return ;
	if (data->map->map[y] && data->map->map[y][x] && ft_strchr("NSEW0",
			data->map->map[y][x]) || replace == '0')
	{
		if (!ft_strchr("NSEW", data->map->map[y][x]))
			data->map->map[y][x] = replace;
		check_flood_fill(data, y + 1, x, replace);
		check_flood_fill(data, y - 1, x, replace);
		check_flood_fill(data, y, x + 1, replace);
		check_flood_fill(data, y, x - 1, replace);
	}
	else
	{
		ft_fprintf(2, "Error\n%sMap not closed or space found%s\n", BOLD_RED,
			RESET);
		free_all_stop(data, 1);
	}
}

static int	check_map(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map->map[++i])
	{
		j = -1;
		while (data->map->map[i][++j])
		{
			if (!ft_strchr("01NSEW ", data->map->map[i][j]))
			{
				ft_fprintf(2, "Error\nChar %s'%c' (L %d, col %d)%s in map is not \
						valid\n", BOLD_RED, data->map->map[i][j], i, j, RESET);
				free_all_stop(data, 1);
			}
			get_player_position(data, data->map->map[i][j], i, j);
		}
	}
	get_player_position(data, 0, -1, -1);
	check_flood_fill(data, data->map->p_y_location - 1, data->map->p_x_location
		- 1, '2');
	check_flood_fill(data, data->map->p_y_location - 1, data->map->p_x_location
		- 1, '0');
	return (0);
}

static void	check_return_in_map(t_data *data, char *line)
{
	static int	start_map = 0;
	static int	in_map = 0;
	static int	line_void = 0;

	if (!ft_strchr("01NSEW ", line[0]))
	{
		ft_fprintf(2, "Error\nChar %s'%c'%s (L %d col 0) in map is not valid\n",
			BOLD_RED, line[0], RESET, data->map->map_h + 1);
		free_all_stop(data, 1);
	}
	if (start_map && in_map && ft_strlen(line) == ft_whitespace(line))
	{
		line_void++;
		in_map = 0;
	}
	else if (ft_strlen(line) > 0)
	{
		start_map = 1;
		in_map = 1;
	}
	if (start_map && in_map && line_void > 0)
	{
		ft_fprintf(2, "Error\n%sreturn (to line in map)%s\n", BOLD_RED, RESET);
		free_all_stop(data, 1);
	}
}

int	parsing_map(t_data *data, int fd, int i)
{
	char	*line;
	int		j;
	int		s;

	j = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[j] && (i || !ft_strchr("	", line[j])))
		{
			s = ft_strlen(line);
			while (s > 0 && ft_strchr(" ", line[s - 1]))
				s--;
			if (s > data->map->map_w)
				data->map->map_w = s;
			data->map->map[i++] = ft_strndup(line, s);
			j = 0;
		}
		check_return_in_map(data, line);
		free(line);
		line = get_next_line(fd);
	}
	return (check_map(data));
}
