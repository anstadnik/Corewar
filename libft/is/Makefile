.PHONY: clean fclean re
CFLAGS = -Wall -Wextra -Werror
ODIR = ../objs/
SDIR = srcs/
IDIR = ../includes/
NAME = is
FILES = ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_isinteger.c \
	ft_isspace.c \
	ft_iswhitespace.c
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
