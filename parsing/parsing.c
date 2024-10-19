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

static int	size_map(char *file, int j, int *error)
{
	int		i;
	int		fd;
	char	*line;

	*error = 0;
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		*error = ft_fprintf(2, "Error : Map impossible to read\n");
	line = get_next_line(fd);
	while (line)
	{
		if (line[j] && ft_strchr("	", line[j]) && ++j)
			continue ;
		free(line);
		line = get_next_line(fd);
		j = 0;
		if (line && line[j])
			i++;
	}
	return (i);
}

static void	test_access_file(t_data *data, char **file)
{
	int	fd;

	fd = ft_strlen(*file) - 1;
	while (fd >= 0 && ft_strchr(" 	", (*file)[fd]))
		(*file)[fd--] = 0;
	fd = open(*file, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(2, "Error : Image '%s%s%s' not found or not accessible\n",
			BOLD_RED, *file, RESET);
		free_all_stop(data, 1);
	}
	close(fd);
}

static int	search_image(t_data *data, char **img, int fd, char *direction)
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
			*img = ft_strndup(line + pass + 2, ft_strlen(line + pass + 2));
			free(line);
			test_access_file(data, img);
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

	data->map->map_h = size_map(file, 0, &i);
	data->map->map = ft_calloc(sizeof(char *), data->map->map_h + 1);
	fd = open(file, O_RDONLY);
	if (fd == -1 && i == 0)
		i = ft_fprintf(2, "Error : Map impossible to read\n");
	if (i == 0 && search_image(data, &data->map->img_no, fd, "NO"))
		i = ft_fprintf(2, "Error : Image NO texture not found\n");
	if (i == 0 && search_image(data, &data->map->img_so, fd, "SO"))
		i = ft_fprintf(2, "Error : Image SO texture not found\n");
	if (i == 0 && search_image(data, &data->map->img_we, fd, "WE"))
		i = ft_fprintf(2, "Error : Image WE texture not found\n");
	if (i == 0 && search_image(data, &data->map->img_ea, fd, "EA"))
		i = ft_fprintf(2, "Error : Image EA texture not found\n");
	if (i == 0 && search_rgb(&data->map->floor_color, fd, "F", &i))
		i = ft_fprintf(2, "Error : RGB Floor color not found\n");
	if (i == 0 && search_rgb(&data->map->ceilling_color, fd, "C", &i))
		i = ft_fprintf(2, "Error : RGB Ceilling color not found\n");
	if (i == 0 && parsing_map(data, fd, 0))
		i = 1;
	if (i)
		free_all_stop(data, 1);
	close(fd);
}
