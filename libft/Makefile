# ecole 42 project | school 21 project
# ft_ls Makefile
# @kcharla, 2020
#
# TO USE DEBUG add `DEBUG=-g' before rule like this: `make DEBUG=-g re'

NAME   := libft.a

CC     := clang
DEBUG  :=
OPTIM  := -O2
CFLAGS := -Wall -Wextra -Werror $(DEBUG) $(OPTIM)

INCLUDE := -I include

BUILD_DIR := build
SRC_DIR   := src
DEPDIR    := $(BUILD_DIR)/.deps

#find src -type f -name '*.c' | sed 'N;N;s/\n/ /g' | sed "s/\$/ \\\\/" | column -t

SRC_FILES := \
src/atoi_itoa/ft_atoi.c        src/atoi_itoa/ft_atoi_base.c    src/atoi_itoa/ft_itoa.c        \
src/atoi_itoa/ft_itoa_base.c   src/atoi_itoa/ft_ldtoa.c        src/atoi_itoa/ft_ldtoa_prec.c  \
src/atoi_itoa/ft_lltoa.c       src/atoi_itoa/ft_mtob.c         src/atoi_itoa/ft_mtob_raw.c    \
src/atoi_itoa/ft_ulltoa.c      src/atoi_itoa/ft_utoa.c         src/atoi_itoa/ft_utoa_base.c   \
src/ft_abs.c                   src/ft_bzero.c                  src/ft_char_to_str.c           \
src/ft_free.c                  src/ft_free_char_2d_arr.c       src/ft_pow.c                   \
src/ft_power_ten.c             src/ft_return.c                 src/ft_tolower.c               \
src/ft_toupper.c               src/ft_word_count.c             src/gnl/get_next_line.c        \
src/is/ft_isalnum.c            src/is/ft_isalpha.c             src/is/ft_isascii.c            \
src/is/ft_isblank.c            src/is/ft_isdigit.c             src/is/ft_isprint.c            \
src/lst/ft_lstadd.c            src/lst/ft_lstappend.c          src/lst/ft_lstdel.c            \
src/lst/ft_lstdelone.c         src/lst/ft_lstiter.c            src/lst/ft_lstmap.c            \
src/lst/ft_lstnew.c            src/mem/ft_mem_rev.c            src/mem/ft_memalloc.c          \
src/mem/ft_memccpy.c           src/mem/ft_memchr.c             src/mem/ft_memcmp.c            \
src/mem/ft_memcpy.c            src/mem/ft_memdel.c             src/mem/ft_memdup.c            \
src/mem/ft_memmove.c           src/mem/ft_memset.c             src/printf/f_after_dot.c       \
src/printf/f_good_way_after.c  src/printf/f_good_way_before.c  src/printf/f_special.c         \
src/printf/flags_c.c           src/printf/flags_di.c           src/printf/flags_f.c           \
src/printf/flags_o.c           src/printf/flags_p.c            src/printf/flags_perc.c        \
src/printf/flags_s.c           src/printf/flags_u.c            src/printf/flags_x.c           \
src/printf/parse_flags.c       src/printf/printf.c             src/printf/resolve_arg.c       \
src/printf/width_format.c      src/put/ft_putchar.c            src/put/ft_putchar_fd.c        \
src/put/ft_putendl.c           src/put/ft_putendl_fd.c         src/put/ft_putendl_free.c      \
src/put/ft_putendl_int_var.c   src/put/ft_puterr_null.c        src/put/ft_puterror.c          \
src/put/ft_putnbr.c            src/put/ft_putnbr_fd.c          src/put/ft_putstr.c            \
src/put/ft_putstr_fd.c         src/put/ft_putstr_free.c        src/str/ft_str_div_by.c        \
src/str/ft_str_div_by_ins.c    src/str/ft_str_dup_rev.c        src/str/ft_str_low.c           \
src/str/ft_str_spam.c          src/str/ft_str_up.c             src/str/ft_strcat.c            \
src/str/ft_strcfnr.c           src/str/ft_strchr.c             src/str/ft_strclr.c            \
src/str/ft_strcmp.c            src/str/ft_strcpy.c             src/str/ft_strdel.c            \
src/str/ft_strdup.c            src/str/ft_strequ.c             src/str/ft_strfnr.c            \
src/str/ft_striter.c           src/str/ft_striteri.c           src/str/ft_strjoin.c           \
src/str/ft_strjoin_free.c      src/str/ft_strlcat.c            src/str/ft_strlen.c            \
src/str/ft_strmap.c            src/str/ft_strmapi.c            src/str/ft_strncat.c           \
src/str/ft_strncmp.c           src/str/ft_strncpy.c            src/str/ft_strndup.c           \
src/str/ft_strnequ.c           src/str/ft_strnew.c             src/str/ft_strnstr.c           \
src/str/ft_strrchr.c           src/str/ft_strrev.c             src/str/ft_strsplit.c          \
src/str/ft_strstr.c            src/str/ft_strsub.c             src/str/ft_strsub_free.c       \
src/str/ft_strtrim.c           src/test/insert_func.c          src/test/insert_mem.c

SRC_FILES_LEN = $(words $(SRC_FILES))

O_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
DEPFILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(DEPDIR)/%.d)

SRC_DIRS = $(shell find $(SRC_DIR) -type d)

HEADER_FILES = include/libft.h include/printf.h

BLACK   := "\e[0;30m"
RED     := "\e[0;31m"
GREEN   := "\e[0;32m"
YELLOW  := "\e[0;33m"
BLUE    := "\e[1;34m"
MAGENTA := "\e[1;35m"
CYAN    := "\e[1;36m"
WHITE   := "\e[1;37m"
RESET   := "\e[0m"

.PHONY: clean fclean all
.PRECIOUS: $(DEPFILES)

all: $(NAME)
	@printf "%b %s %b\n" $(CYAN) "$(NAME) is ready" $(RESET)

$(NAME): $(O_FILES)
	@ranlib $(NAME)
	@printf "%b %s compiled %b\n" $(GREEN) $(NAME) $(RESET)

$(BUILD_DIRS_REC):
	@mkdir -vp $(BUILD_DIRS_REC)

INDEX = 0

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c  $(DEPDIR)/%.d
	@make -j $(DEPDIR)/%.d
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDE) -c -o $@ $<
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))
	@printf "%b #%3.3s of %3.3s : %s %b\n" $(YELLOW) $(INDEX) $(SRC_FILES_LEN) $@ $(RESET)
	@ar rcs $(NAME) $@

$(DEPDIR)/%.d:
	@mkdir -p $(@D)

clean:
	@rm -rf $(BUILD_DIR)
	@printf "%b %s successfully cleaned %b\n" $(BLUE) $(NAME) $(RESET)

fclean: clean
	@rm -f $(NAME)
	@printf "%b %s fully cleaned %b\n" $(RED) $(NAME) $(RESET)

re: fclean all
	@printf "%b %s recompiled %b\n" $(GREEN) $(NAME) $(RESET)

$(DEPFILES):

-include $(wildcard $(DEPFILES))