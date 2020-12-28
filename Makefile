WHITE		= "\\033[0m"
CYAN		= "\\033[36m"
GREEN		= "\\033[32m"

NAME =		libft_malloc_$(HOSTTYPE).so
SL_NAME =	libft_malloc.so
CC =		gcc
CFLAGS = 	-Wall -Wextra -Werror -g -fsanitize=address

INC_DIR =	includes/
SRC_DIR =	src/
BIN_DIR =	bin/

SRC_FILES =	malloc.c \
			realloc.c \
			free.c \
			show_alloc_mem.c \
			show_pages_content.c \
			utils.c \

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
BINS = $(addprefix $(BIN_DIR), $(SRC_FILES:.c=.o))

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

all: $(NAME)

$(NAME): $(BIN_DIR) $(BINS)
	@printf "$(CYAN)[WAIT]$(WHITE) Compiling into %-50s\r" $(NAME)
	@$(CC) $(CFLAGS) $(BINS) -shared -o $(NAME)
	@printf "$(GREEN)[OK]$(WHITE) %s has been well compiled\n" $(NAME)
	@printf "$(CYAN)[WAIT]$(WHITE) Creating %-50s\r" $(SL_NAME)
	@ln -fs ${NAME} ${SL_NAME}
	@printf "$(GREEN)[OK]$(WHITE) %s has been well created\n" $(SL_NAME)

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
	@rm -f $(SL_NAME)
	@printf "$(GREEN)[OK]$(WHITE) fclean done\n"

re: fclean all

.PHONY: all re run clean fclean
