/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:26:23 by hle-roux          #+#    #+#             */
/*   Updated: 2024/08/29 16:40:28 by hle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "get_next_line.h"
#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	buffer = (char *)malloc(sizeof(char)
			* (ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (buffer == NULL)
		return (NULL);
	while (s1[i])
	{
		buffer[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		buffer[i] = s2[j];
		i++;
		j++;
	}
	buffer[i] = '\0';
	return (buffer);
}

int	find_n(char *s1)
{
	int	i;

	i = 0;
	if (s1 == NULL)
		return (-1);
	while (s1[i])
	{
		if (s1[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen_gnl(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	i = 0;
	while (str && str[i] != '\0')
		i++;
	return (i);
}

void	ft_free(char *freeme)
{
	if (freeme)
		free (freeme);
	freeme = NULL;
}

char	*set_zero(char *tampon, char *str)
{
	tampon = str;
	if (tampon == NULL)
	{
		tampon = (char *)malloc(sizeof(char));
		if (!tampon)
			return (NULL);
		tampon[0] = '\0';
	}
	return (tampon);
}
