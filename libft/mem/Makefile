.PHONY: clean fclean re
CFLAGS = -Wall -Wextra -Werror
ODIR = ../objs/
SDIR = srcs/
IDIR = ../includes/
NAME = mem
FILES = ft_bzero.c \
	ft_memalloc.c \
	ft_memccpy.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memdel.c \
	ft_memdup.c \
	ft_memmove.c \
	ft_memset.c \
	ft_realloc.c
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
