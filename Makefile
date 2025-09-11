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
BONUS = checker

SRC_DIR = ./src

C_FILES = main.c parsing.c utils.c stack.c \
		index.c quicksort.c b_moves.c a_moves.c \
		push_swap.c small_sort.c both_moves.c \
		push_swap_utils.c execute_moves.c

C_BONUS = bonus/checker.c bonus/get_next_line.c bonus/get_next_line_utils.c \
		a_moves.c b_moves.c both_moves.c index.c parsing.c \
		quicksort.c stack.c utils.c

SRC = $(addprefix $(SRC_DIR)/, $(C_FILES))

BONUS_SRC = $(addprefix $(SRC_DIR)/, $(C_BONUS))
BONUS_OBJ = $(BONUS_SRC:.c=.o)

OBJ = $(SRC:.c=.o)

INCLUDES = headers

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I$(INCLUDES) $(OBJ) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

bonus: $(BONUS_OBJ)
	$(CC) $(CFLAGS) -I$(INCLUDES) $(BONUS_OBJ) -o $(BONUS)

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re
