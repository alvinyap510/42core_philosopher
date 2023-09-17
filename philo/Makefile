# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alyap <alyap@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/17 22:41:21 by alyap             #+#    #+#              #
#    Updated: 2023/09/17 23:02:37 by alyap            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= philo

CC 			= gcc
CFLAGS		= -Werror -Wextra -Wall

SRC_DIR 	= ./src/
OBJ_DIR		= ./obj/
SRC			= $(wildcard $(SRC_DIR)*.c)
OBJ			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))
HEADERS		= ./includes/
INCLUDES	= -I$(HEADERS)

all				:	$(NAME)

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
					mkdir -p $(OBJ_DIR)
					$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME)			:	$(OBJ)
					$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(NAME)

clean			:	
					rm -rf $(OBJ_DIR)

fclean			:	clean
					rm -f $(NAME)

re				:	fclean all

.PHONY			: 	all clean fclean re
