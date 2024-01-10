# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/03 14:09:27 by aabouqas          #+#    #+#              #
#    Updated: 2024/01/09 17:04:28 by aabouqas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = client.c server.c
SRC_OBJ = $(SRC:.c=.o)

NAME = client server client_bonus server_bonus
BONUS_SRC = client_bonus.c server_bonus.c
BONUS_OBJ = $(BONUS_SRC:.c=.o)

C_REQ = client.c utils.c minitalk.h
S_REQ = server.c utils.c minitalk.h

CB_REQ = client_bonus.c utils_bonus.c minitalk_bonus.h
SB_REQ = server_bonus.c utils_bonus.c minitalk_bonus.h

all: $(SRC_OBJ)

client.o: $(C_REQ)
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) client.o utils.c -o client

server.o: $(S_REQ)
	$(CC) $(CFLAGS) -c server.c
	$(CC) $(CFLAGS) server.o utils.c -o server


bonus: $(BONUS_OBJ)

client_bonus.o: $(CB_REQ)
	$(CC) $(CFLAGS) -c client_bonus.c
	$(CC) $(CFLAGS) client_bonus.o utils_bonus.c -o client_bonus

server_bonus.o: $(SB_REQ)
	$(CC) $(CFLAGS) -c server_bonus.c
	$(CC) $(CFLAGS) server_bonus.o utils_bonus.c -o server_bonus

re: fclean all

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(SRC_OBJ) $(BONUS_OBJ) utils.o utils_bonus.o

.PHONY: all bonus re fclean clean