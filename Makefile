#RTv1 Makefile
#@kcharla, 2010

NAME = ft_ls

CC = clang

LIBM =
DEBUG =
OPTIM = -O2

CFLAGS = -Wall -Wextra -Werror $(DEBUG) $(OPTIM)

LIB_FT = libft
LIB_FT_FILE = $(LIB_FT)/libft.a

INCLUDE = -I include/ -I $(LIB_FT)/include/

# find include -type f -name '*.h' | sed "s/\$/ \\\\/"
HEADERS = \
include/ft_ls.h

BUILD_DIR = build/
SRC_DIR = src/

#SRC_FILES = $(shell find $(SRC_DIR) -not \( -path $(MAIN_DIR) -prune \) -type f -name "*.c")
# find src -type f -name '*.c' | sed "s/\$/ \\\\/"

SRC_FILES = \
src/main.c


O_FILES = $(patsubst $(SRC_DIR)%.c, $(BUILD_DIR)%.o, $(SRC_FILES))

SRC_DIRS = $(shell find $(SRC_DIR) -type d)
BUILD_DIRS_REC = $(patsubst $(SRC_DIR)%, $(BUILD_DIR)%, $(SRC_DIRS))

.PHONY: clean fclean all

all: $(NAME)

$(NAME): $(LIB_FT_FILE) $(BUILD_DIRS_REC) $(O_FILES)
	@echo "\033[0;32m" "Building RTv1 executable..." "\033[0m"
	$(CC) $(CFLAGS) $(O_FILES) $(INCLUDE) -o $(NAME) $(LIB_FT_FILE) $(LIBM)
	@echo "\033[0;32m" "Done" "\033[0m"

$(LIB_FT_FILE):
	@make DEBUG=$(DEBUG) -C $(LIB_FT)

$(BUILD_DIRS_REC):
	@mkdir -vp $(BUILD_DIRS_REC)

$(BUILD_DIR)%.o: $(SRC_DIR)%.c ${HEADERS}
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<
	@echo "\033[0;32m"
	@printf "%-30s | %-25s" $@ $<
	@echo "\033[0m"

clean:
	@make -C $(LIB_FT) clean
	@rm -rf $(BUILD_DIR)
	@echo "make: Done clean of \`$(NAME)'."

fclean: lclean
	@make fclean -C $(LIB_FT)
	@rm -f $(NAME)
	@echo "make: Done full clean of \`$(NAME)'."

re: fclean all
	@echo "make: Done recompile of \`$(NAME)'."

lclean:
	@rm -rf $(BUILD_DIR)
	@echo "make: Done local clean of \`$(NAME)'."

lfclean: lclean
	@rm -f $(NAME)
	@echo "make: Done local full clean of \`$(NAME)'."

lre: lfclean all
	@echo "make: Done local recompile of \`$(NAME)'."
