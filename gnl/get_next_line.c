/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:55:33 by hle-roux          #+#    #+#             */
/*   Updated: 2024/08/29 16:40:25 by hle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*static_str;
	char		*buffer;
	char		*ligne;
	char		*tampon;

	if (fd <= -1 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd == FOPEN_MAX)
	{
		ft_free(static_str);
		static_str = NULL;
		return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	tampon = NULL;
	static_str = get_lines(static_str, buffer, tampon, fd);
	if (static_str == NULL)
	{
		ft_free(static_str);
		return (NULL);
	}
	ligne = extract_line(static_str);
	static_str = cut_line(static_str);
	return (ligne);
}

char	*get_lines(char *str, char *buffer, char *tampon, int fd)
{
	int	i;

	i = 1;
	while (i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			ft_free(str);
			return (NULL);
		}
		if (i == 0)
		{
			ft_free(buffer);
			return (str);
		}
		buffer[i] = '\0';
		tampon = set_zero(tampon, str);
		str = ft_strjoin(tampon, buffer);
		ft_free(tampon);
		if (find_n(str) == 1)
			break ;
	}
	ft_free(buffer);
	return (str);
}

char	*extract_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (str == NULL || str[0] == '\0')
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (ft_return(line, str))
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = '\n';
		line[i + 1] = '\0';
	}
	else if (str[i] == '\0')
		line[i] = '\0';
	return (line);
}

char	*cut_line(char *str)
{
	int		i;
	int		t;
	char	*scrap;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		ft_free(str);
		return (NULL);
	}
	t = ft_strlen_gnl(str);
	scrap = (char *)malloc(sizeof(char) * (t - i));
	if (ft_return(scrap, str))
		return (NULL);
	t = 0;
	i++;
	while (str[i] != '\0')
		scrap[t++] = str[i++];
	scrap[t] = '\0';
	ft_free(str);
	return (scrap);
}

int	ft_return(char *char_test, char *to_free)
{
	if (char_test == NULL)
	{
		ft_free(to_free);
		return (1);
	}
	return (0);
}
