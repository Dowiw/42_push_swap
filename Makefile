# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/31 09:57:15 by kmonjard          #+#    #+#              #
#    Updated: 2025/08/06 09:36:27 by kmonjard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

SRC_DIR = ./src
C_FILES = ft_push_swap.c
SRC = $(addprefix $(SRC_DIR)/, $(C_FILES))

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
