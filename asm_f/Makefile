.PHONY: clean fclean re r
CC = gcc
CFLAGS = -Wall -Wextra -Werror
ODIR = objs/
SDIR = srcs/
IDIR = includes/
LDIR = ../libft/
NAME = asm
LIB = $(LDIR)libft.a
FILES = bytecode.c del.c exit.c label.c label2.c main.c other.c parse_arg.c parse_args.c\
        parse_code.c parser_checks.c parser_error.c parser_other.c\
        parsing_name_and_comment.c parsing_name_and_comment2.c\
        things_to_bytecode.c

OBJS = $(FILES:.c=.o)

all: $(NAME)
	
$(NAME): $(LIB) $(addprefix $(ODIR), $(OBJS))
	@echo "\x1b[34m\nCompiling $@\x1b[0m"
	@$(CC) $(CFLAGS) -I $(IDIR) -I $(LDIR)includes -o $@ $^

$(LIB):
	@echo "\x1b[35m\nCompiling $(notdir $@)\x1b[0m"
	@$(MAKE) -C $(dir $@) $(notdir $@)
	@echo "\x1b[35m\n$(notdir $@) compiled\x1b[0m"

$(addprefix $(ODIR), %.o): $(addprefix $(SDIR), %.c)
	@printf "."
	@$(CC) $(CFLAGS) -I $(IDIR) -I $(LDIR)includes -c -o $@ $<

r: $(NAME)
	./$(NAME)
	# parameters

clean: clean_objs
	@$(MAKE) -C $(LDIR) clean

clean_objs:
	@echo "\x1b[31mRemoving the object files of $(NAME)\x1b[0m"
	@rm -f $(addprefix $(ODIR), $(OBJS))

fclean: clean_objs
	@$(MAKE) -C $(LDIR) fclean
	@echo "\x1b[31mRemoving the $(NAME)\x1b[0m"
	@rm -rf $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE)
