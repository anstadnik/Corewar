.PHONY: clean fclean re
CFLAGS = -Wall -Wextra -Werror
ODIR = ../objs/
SDIR = srcs/
IDIR = ../includes/
NAME = put
FILES = ft_putchar.c \
	ft_putchar_fd.c \
	ft_putendl.c \
	ft_putendl_fd.c \
	ft_putnbr.c \
	ft_putnbr_fd.c \
	ft_putstr.c \
	ft_putstr_fd.c
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
