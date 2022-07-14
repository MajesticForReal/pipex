# **************************************************************************** #                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/31 15:05:46 by anrechai          #+#    #+#              #
#    Updated: 2022/06/13 18:23:45 by anrechai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	main.c fork.c split.c utils.c utils2.c

OBJS		=	${SRCS:.c=.o}

NAME		=	pipex

CFLAGS		=	-Wall -Wextra -Werror

CC			=	cc

HEADER		=	pipex.h

%.o:%.c
			$(CC) $(CFLAGS) -c $< -o $@ -I./

$(NAME):	${OBJS}
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L.

all:		$(NAME)

clean:
			rm -f ${OBJS}
			@echo "\033[92mstatus $@ is [OK]\033[0m"

fclean:		clean
			rm -f ${NAME}
			@echo "\033[92mstatus $@ [OK]\033[0m"

re:			fclean all

.PHONY:		fclean clean re all
