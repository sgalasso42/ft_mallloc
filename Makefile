# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/23 15:17:28 by sgalasso          #+#    #+#              #
#    Updated: 2019/10/23 17:07:54 by sgalasso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= a.out
CC 			= gcc
CFLAGS 		= -Wall -Wextra -Werror -g -fsanitize=address

SRC_PATH 	= srcs/
OBJ_PATH 	= objs/
INC_PATH	= includes/ \
			  libft/includes/
LIBFT 		= libft/

WHITE       = "\\033[0m"
CYAN        = "\\033[36m"
GREEN       = "\\033[32m"

SRC_NAME 	= main.c \
			ft_malloc.c \
			ft_free.c \
			show_alloc_mem.c \
			show_pages_content.c \
			utils_functions.c \

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	@Make -C $(LIBFT)
	@printf "$(CYAN)[WAIT]$(WHITE) Compiling into %-50s\r" $(NAME)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L$(LIBFT) -lft $(INC)
	@printf "$(GREEN)[OK]$(WHITE) %s has been well compiled\n" $(NAME)

$(OBJ) : | $(OBJ_PATH)

$(OBJ_PATH) :
	@mkdir objs

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC_PATH) Makefile
	@printf "$(CYAN)[WAIT]$(WHITE) Compiling into .o %-50s\r" $@
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@make -C $(LIBFT) clean
	@rm -rf $(OBJ_PATH)
	@printf "$(GREEN)[OK]$(WHITE) Clean done\n"

fclean: clean
	@make -C $(LIBFT) fclean
	@rm -f $(NAME)
	@printf "$(GREEN)[OK]$(WHITE) Fclean done\n"

re: fclean all

.PHONY: all re clean fclean
