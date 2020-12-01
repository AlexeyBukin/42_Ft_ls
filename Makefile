# ecole 42 project | school 21 project
# ft_ls Makefile
# @kcharla, 2020

BLACK   := "\e[0;30m"
RED     := "\e[0;31m"
GREEN   := "\e[0;32m"
YELLOW  := "\e[0;33m"
BLUE    := "\e[1;34m"
MAGENTA := "\e[1;35m"
CYAN    := "\e[1;36m"
WHITE   := "\e[1;37m"
RESET   := "\e[0m"
INDEX   := 1

NAME    := ft_ls

CC      := gcc
DEBUG   := -g
OPTIM   := -O2
CFLAGS  := -Wall -Wextra -Werror $(DEBUG) $(OPTIM)

BUILD_DIR := build
OBJ_DIR   := $(BUILD_DIR)/obj
SRC_DIR   := src

LIB_FT_DIR  := libft
LIB_FT_FILE := $(LIB_FT_DIR)/libft.a
INCLUDE     := -I include/ -I $(LIB_FT_DIR)/include/

# find src -type f -name '*.c' | sort | column -c 100 | sed 's/$/ \\\\/'
SRC_FILES := \
src/ls_debug.c                  src/ls_orders.c                 src/ls_print_order.c \
src/ls_entry.c                  src/ls_orders_arrange.c         src/ls_sort.c \
src/ls_errors.c                 src/ls_orders_create_rec.c      src/ls_sort_compare.c \
src/ls_flags.c                  src/ls_orders_fill_stat.c       src/ls_sort_merge.c \
src/ls_free.c                   src/ls_print.c                  src/main.c \

SRC_FILES_LEN := $(words $(SRC_FILES))
OBJ_FILES     := $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY:    clean fclean all re lclean lfclean lre

all: $(NAME)
	@printf "%b %s %b\n" $(CYAN) "$(NAME) is ready" $(RESET)

$(NAME): $(LIB_FT_FILE) $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(INCLUDE) -o $(NAME) $(LIB_FT_FILE)
	@printf "%b %s compiled %b\n" $(GREEN) $(NAME) $(RESET)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -vp $(@D)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "%b %s / %s : %s\n" $(YELLOW) $(INDEX) $(SRC_FILES_LEN) $@
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

$(LIB_FT_FILE):
	@make DEBUG=$(DEBUG) OPTIM=$(OPTIM) -C $(LIB_FT_DIR)

clean:
	@make clean -C $(LIB_FT_DIR)
	@rm -rf $(BUILD_DIR)
	@printf "%b %s successfully cleaned %b\n" $(BLUE) $(NAME) $(RESET)

fclean: lclean
	@make fclean -C $(LIB_FT_DIR)
	@rm -f $(NAME)
	@printf "%b %s fully cleaned %b\n" $(RED) $(NAME) $(RESET)

re: fclean all
	@printf "%b %s recompiled %b\n" $(GREEN) $(NAME) $(RESET)

lclean:
	@rm -rf $(BUILD_DIR)
	@printf "%b %s locally cleaned %b\n" $(BLUE) $(NAME) $(RESET)

lfclean: lclean
	@rm -f $(NAME)
	@printf "%b %s locally full-cleaned %b\n" $(RED) $(NAME) $(RESET)

lre: lfclean all
	@printf "%b %s locally recompiled %b\n" $(GREEN) $(NAME) $(RESET)

