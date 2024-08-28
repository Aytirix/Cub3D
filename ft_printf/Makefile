# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hle-roux <hle-roux@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 17:02:02 by hle-roux          #+#    #+#              #
#    Updated: 2023/01/20 15:21:10 by hle-roux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	ft_printf.c \
		annex1.c \
		annex2.c \
		annex3.c

OBJ = ${SRC:.c=.o}

NAME = libftprintf.a

HEADER = .

.c.o:
	gcc -Wall -Werror -Wextra -I ${HEADER} -c $< -o ${<:.c=.o}

all: $(NAME)


$(NAME) : $(OBJ)
	ar rc $@ $(OBJ)


clean :
	/bin/rm -f ${OBJ}

fclean : clean
	/bin/rm -f $(NAME)

re : fclean $(NAME)
