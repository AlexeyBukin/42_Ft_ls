# Makefile for ft_ls project in school 21 (ecole 42)
# written by kcharla, (15.02.2020)
#
# TO USE DEBUG add `DEBUG=-g' before rule like this: `make DEBUG=-g re'

NAME = ft_ls

CC = clang
DEBUG =
OPTIM = -O2

CFLAGS = -Wall -Wextra -Werror $(DEBUG) $(OPTIM)

INCLUDE = -I include/

BUILD_DIR = build/
SRC_DIR = src/

#SRC_FILES = $(shell find $(SRC_DIR) -not \( -path $(MAIN_DIR) -prune \) -type f -name "*.c")
#find src -type f -name '*.c' | sed "s/\$/ \\\\/" | cut -c 3-

SRC_FILES = \
src/main.c

O_FILES = $(patsubst $(SRC_DIR)%.c, $(BUILD_DIR)%.o, $(SRC_FILES))

SRC_DIRS = $(shell find $(SRC_DIR) -type d)
BUILD_DIRS_REC = $(patsubst $(SRC_DIR)%, $(BUILD_DIR)%, $(SRC_DIRS))

HEADER_FILES = include/libft.h include/printf.h

.PHONY: clean fclean all

all: $(NAME)

$(NAME): $(BUILD_DIRS_REC) $(O_FILES)
	@ranlib $(NAME)
	@echo "make: Done compilation of \`$(NAME)'."

$(BUILD_DIRS_REC):
	@mkdir -vp $(BUILD_DIRS_REC)

$(BUILD_DIR)%.o: $(SRC_DIR)%.c $(HEADER_FILES)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<
	@ar rcs $(NAME) $@

clean:
	@rm -rf $(BUILD_DIR)
	@echo "make: Done clean of \`$(NAME)'."

fclean: clean
	@rm -f $(NAME)
	@echo "make: Done full clean of \`$(NAME)'."

re: fclean all
	@echo "make: Done recompile of \`$(NAME)'."
