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

static int	size_map(char *file, int *error)
{
	int		i;
	int		fd;
	char	*line;

	*error = 0;
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		*error = ft_fprintf(2, "Error\nMap impossible to read\n");
	line = get_next_line(fd);
	while (line)
	{
		if (line && line[0] && ft_strchr(" 01", line[0]))
			i++;
		free(line);
		line = get_next_line(fd);
	}
	return (i);
}

static void	test_access_file(t_data *data, t_texture *tx)
{
	int	fd;

	fd = ft_strlen(tx->name) - 1;
	while (fd >= 0 && ft_strchr(" 	", tx->name[fd]))
		tx->name[fd--] = 0;
	fd = open(tx->name, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(2, "Error\nImage '%s%s%s' not found or not accessible\n",
			BOLD_RED, tx->name, RESET);
		free_all_stop(data, 1);
	}
	close(fd);
}

static int	search_image(t_data *data, t_texture *tx, int fd, char *direction)
{
	char	*line;
	int		pass;

	pass = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[pass] && ft_strchr(" 	", line[pass]) && ++pass)
			continue ;
		if (ft_strncmp(direction, line + pass, 2) == 0)
		{
			while (ft_strchr(" 	", line[pass + 2]))
				pass++;
			tx->name = ft_strndup(line + pass + 2, ft_strlen(line + pass + 2));
			free(line);
			test_access_file(data, tx);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
		pass = 0;
	}
	return (1);
}

void	parsing(t_data *data, char *file)
{
	int	i;
	int	fd;

	data->map->map_h = size_map(file, &i);
	data->map->map = ft_calloc(sizeof(char *), data->map->map_h + 1);
	fd = open(file, O_RDONLY);
	if (fd == -1 && i == 0)
		i = ft_fprintf(2, "Error\nMap impossible to read\n");
	if (i == 0 && search_image(data, data->map->img_no, fd, "NO"))
		i = ft_fprintf(2, "Error\nImage NO texture not found\n");
	if (i == 0 && search_image(data, data->map->img_so, fd, "SO"))
		i = ft_fprintf(2, "Error\nImage SO texture not found\n");
	if (i == 0 && search_image(data, data->map->img_we, fd, "WE"))
		i = ft_fprintf(2, "Error\nImage WE texture not found\n");
	if (i == 0 && search_image(data, data->map->img_ea, fd, "EA"))
		i = ft_fprintf(2, "Error\nImage EA texture not found\n");
	if (i == 0 && search_rgb(&data->map->floor_color, fd, "F", &i))
		i = ft_fprintf(2, "Error\nRGB Floor color not found\n");
	if (i == 0 && search_rgb(&data->map->ceilling_color, fd, "C", &i))
		i = ft_fprintf(2, "Error\nRGB Ceilling color not found\n");
	if (i == 0 && parsing_map(data, fd, 0))
		i = 1;
	if (i)
		free_all_stop(data, 1);
	close(fd);
}
