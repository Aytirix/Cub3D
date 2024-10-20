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

static int	convert_rgb(char *rgb, int i, int *color)
{
	int	tmp;
	int	virgule;

	virgule = 0;
	while (rgb[i] || virgule <= 2)
	{
		tmp = ft_atoi(rgb + i);
		if (tmp < 0 || tmp > 255 || virgule > 2)
			return (ft_fprintf(2, "Error\nRGB color not valid\n"));
		*color = (*color << 8) + tmp;
		while (ft_isdigit(rgb[i]))
			i++;
		while (rgb[i] && ft_strchr(" \t,", rgb[i]))
			i++;
		if (rgb[i] == ',')
			i++;
		if (rgb[i] && (!ft_strchr("0123456789 \t", rgb[i])))
			return (ft_fprintf(2, "Error\nRGB caractere '%s%c%s' not valid\n",
					BOLD_RED, rgb[i], RESET));
		++virgule;
	}
	return (0);
}

int	search_rgb(int *rgb, int fd, char *direction, int *err)
{
	char	*line;
	int		pass;

	pass = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[pass] && ft_strchr(" 	", line[pass]) && ++pass)
			continue ;
		if (ft_strncmp(direction, line + pass, 1) == 0)
		{
			while (ft_strchr(" 	", line[pass + 1]))
				pass++;
			*err = convert_rgb(line + pass + 1, 0, rgb);
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
		pass = 0;
	}
	return (1);
}
