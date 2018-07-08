.PHONY: clean fclean re
CFLAGS = -Wall -Wextra -Werror
ODIR = ../objs/
SDIR = srcs/
IDIR = ../includes/
NAME = lst
FILES = ft_lstadd.c \
	ft_lstaddb.c \
	ft_lstdel.c \
	ft_lstdelnode.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lstpushb.c \
	ft_lstpushf.c \
	ft_lsttostr.c \
    str_from_lsts.c
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
