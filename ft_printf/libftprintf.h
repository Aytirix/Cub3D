/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roux <hle-roux@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:09:19 by hle-roux          #+#    #+#             */
/*   Updated: 2023/01/20 15:21:10 by hle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		ft_putchar(char c);
int		ft_putnbr(int nb);
int		ft_putunbr(unsigned int c);
int		ft_putstr(char *str);
char	*ft_strchr(const char *str, int c);
int		ft_intlen(int n);
int		ft_strlen(char *str);
int		ft_putptr(unsigned long long ptr);
int		ft_puthex(unsigned int n);
int		ft_putuhex(unsigned int n);
int		ft_puthexamaj(unsigned long long nb);
int		ft_puthexamin(unsigned long long nb);

#endif
