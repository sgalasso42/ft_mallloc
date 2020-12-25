WHITE		= "\\033[0m"
CYAN		= "\\033[36m"
GREEN		= "\\033[32m"

NAME =		ft_malloc
CC =		gcc
CFLAGS = 	-Wall -Wextra -Werror#-g -fsanitize=address

INC_DIR =	includes/
SRC_DIR =	src/
BIN_DIR =	bin/

SRC_FILES =	main.c \
			ft_malloc.c \
			ft_free.c \
			show_alloc_mem.c \
			show_pages_content.c \
			utils_functions.c \
			ft_memset.c \
			ft_bzero.c \

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
BINS = $(addprefix $(BIN_DIR), $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(BIN_DIR) $(BINS)
	@printf "$(CYAN)[WAIT]$(WHITE) Compiling into %-50s\r" $(NAME)
	@$(CC) $(CFLAGS) $(BINS) -o $(NAME)
	@printf "$(GREEN)[OK]$(WHITE) %s has been well compiled\n" $(NAME)

NB = $(words $(SRC_FILES))
$(eval MAX=$(shell echo $$(($(NB) - 1))))
$(BIN_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)/ft_malloc.h Makefile
	@$(eval INDEX=$(shell echo $$(($(INDEX) + 1))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<
	@printf "$(CYAN)[Compiling]$(WHITE) $(CYAN)[$(WHITE)%d%%$(CYAN)]$(WHITE) %s\r" $(PERCENT) $@;

$(BIN_DIR):
	@mkdir -p bin

clean:
	@rm -rf $(BIN_DIR)
	@printf "$(GREEN)[OK]$(WHITE) clean done\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(GREEN)[OK]$(WHITE) fclean done\n"

re: fclean all

.PHONY: all re clean fclean
