/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:50:49 by hle-roux          #+#    #+#             */
/*   Updated: 2023/07/10 21:52:19 by hle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*get_lines(char *str, char *buffer, char *tampon, int fd);
char	*extract_line(char *str);
char	*cut_line(char *str);
int		find_n(char *s1);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen_gnl(char *str);
void	ft_free(char *freeme);
char	*ft_split(char *too_long);
int		ft_return(char *char_test, char *to_free);
char	*set_zero(char *tampon, char *str);

#endif
