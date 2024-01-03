# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/03 14:09:27 by aabouqas          #+#    #+#              #
#    Updated: 2024/01/03 14:12:13 by aabouqas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = client.c server.c
NAME = client server client_bonus server_bonus
BONUS_SRC = client_bonus.c server_bonus.c
BONUS_OBJ = $(BONUS_SRC:.c=.o)
SRC_OBJ = $(SRC:.c=.o)

all: $(SRC_OBJ)

client.o: client.c minitalk.h
	$(CC) $(CFLAGS) -c client.c -o client.o
	$(CC) $(CFLAGS) client.o -o client

server.o: server.c minitalk.h
	$(CC) $(CFLAGS) -c server.c -o server.o
	$(CC) $(CFLAGS) server.o -o server

bonus: $(BONUS_OBJ)

client_bonus.o: client_bonus.c minitalk_bonus.h
	$(CC) $(CFLAGS) -c client_bonus.c
	$(CC) $(CFLAGS) client_bonus.o -o client_bonus

server_bonus.o: server_bonus.c minitalk_bonus.h
	$(CC) $(CFLAGS) -c server_bonus.c
	$(CC) $(CFLAGS) server_bonus.o -o server_bonus

re: fclean all

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(SRC_OBJ) $(BONUS_OBJ)

.PHONY: all bonus re fclean clean