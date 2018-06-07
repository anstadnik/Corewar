.PHONY: clean fclean re r
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wconversion#remove last one
ODIR = objs/
SDIR = srcs/
IDIR = includes/
LDIR = ../libft/
NAME = asm
LIB = $(LDIR)libft.a
FILES = main.c
OBJS = $(FILES:.c=.o)

ifeq ($(shell uname), Linux)
	ESCAPE := \033
else
	ESCAPE := \x1b
endif

all: $(NAME)
	
$(NAME): $(LIB) $(addprefix $(ODIR), $(OBJS))
	@echo "$(ESCAPE)[34m\nCompiling $@$(ESCAPE)[0m"
	@$(CC) $(CFLAGS) -I $(IDIR) -I $(LDIR)includes -o $@ $^

$(LIB):
	@echo "$(ESCAPE)[35m\nCompiling $(notdir $@)$(ESCAPE)[0m"
	@$(MAKE) --no-print-directory -C $(dir $@) $(notdir $@)
	@echo "$(ESCAPE)[35m\n$(notdir $@) compiled$(ESCAPE)[0m"

$(addprefix $(ODIR), %.o): $(addprefix $(SDIR), %.c)
	@printf "."
	@$(CC) $(CFLAGS) -I $(IDIR) -I $(LDIR)includes -c -o $@ $<

r: $(NAME)
	./$(NAME)
	# parameters

clean: clean_objs
	@$(MAKE) --no-print-directory -C $(LDIR) clean

clean_objs:
	@echo "$(ESCAPE)[31mRemoving the object files of $(NAME)$(ESCAPE)[0m"
	@rm -f $(addprefix $(ODIR), $(OBJS))

fclean: clean_objs
	@$(MAKE) --no-print-directory -C $(LDIR) fclean
	@echo "$(ESCAPE)[31mRemoving the $(NAME)$(ESCAPE)[0m"
	@rm -rf $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE)
