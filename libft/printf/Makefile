.PHONY: clean fclean re
CFLAGS = -Wall -Wextra -Werror -Wconversion
ODIR = ../objs/
SDIR = srcs/
IDIR = ../includes/
NAME = print
FILES = ft_printf.c \
	printf_char.c \
	printf_fill_list.c \
	printf_funcs.c \
	printf_get_params.c \
	printf_int.c \
	printf_make_str.c \
	printf_parse.c \
	printf_process_conv.c \
	printf_ptr.c \
	printf_str.c \
	printf_parse2.c \
	printf_flags_hand.c \
	printf_time.c \
	printf_row_str.c \
	printf_caesar.c \
	printf_memory.c
OBJS = $(FILES:.c=.o)

ifeq ($(shell uname), Linux)
	ESCAPE := \033
	CC = clang
else
	ESCAPE := \x1b
	CC = gcc
endif

all: $(addprefix $(ODIR), $(OBJS))

$(addprefix $(ODIR), %.o): $(addprefix $(SDIR), %.c)
	@$(CC) $(CFLAGS) -I$(IDIR) -c -o $@ $<
	@printf "."

clean:
	@echo "$(ESCAPE)[31mRemoving the object files of $(NAME)$(ESCAPE)[0m"
	@rm -f $(addprefix $(ODIR), $(OBJS))

fclean: clean

re:
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory 
