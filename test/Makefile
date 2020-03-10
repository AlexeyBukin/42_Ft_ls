# ecole 42 project | school 21 project
# proj_example Makefile
# @kcharla, 2020

NAME = ft_ls

CC = clang

TARGET = MACOSX

DEBUG =
OPTIM = -O2

CFLAGS = -Wall -Wextra -Werror $(DEBUG) $(OPTIM)

BUILD_DIR = build
SRC_DIR = src

LIB_FT = libft
LIB_FT_FILE = $(LIB_FT)/libft.a

INCLUDE = -I include/ -I $(LIB_FT)/include/

# find src -type f -name '*.c' | sed "s/\$/ \\\\/"
SRC_FILES = \
src/main.c\
src/inn/second.c

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

DEPDIR := $(BUILD_DIR)/.deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

.PHONY: clean fclean all

all: $(NAME)

$(NAME): $(LIB_FT_FILE) $(OBJ_FILES)
	@echo "\033[0;32m" "Building $(NAME) executable..." "\033[0m"
	$(CC) $(CFLAGS) $(OBJ_FILES) $(INCLUDE) -o $(NAME) $(LIB_FT_FILE)
	@echo "\033[0;32m" "Done" "\033[0m"

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c $(DEPDIR)/%.d
	mkdir -p $(@D)
	gcc $(DEPFLAGS) -c $< -o $@ -I include

$(LIB_FT_FILE):
	@make DEBUG=$(DEBUG) -C $(LIB_FT)

$(DEPDIR)/%.d:
	mkdir -p $(@D)

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


DEPFILES := $(SRC_FILES:$(SRC_DIR)/%.c=$(DEPDIR)/%.d)

$(DEPFILES):
-include $(wildcard $(DEPFILES))