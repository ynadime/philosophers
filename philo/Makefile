# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynadime <ynadime@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 14:49:55 by ynadime           #+#    #+#              #
#    Updated: 2025/06/03 14:49:56 by ynadime          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = philosophers.c \
	  init.c \
	  simulation.c \
	  routine.c \
	  utils.c \
	  mem_utils.c \
	  
OBJS = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -lreadline

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re