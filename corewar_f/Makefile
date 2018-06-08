.PHONY: clean fclean re r g
CFLAGS = -Wall -Wextra -Werror -Wconversion#remove last one
ODIR = objs/
SDIR = srcs/
IDIR = includes/
LDIR = ../libft/
NAME = corewar
LIB = $(LDIR)libft.a
FUNCS = fork_func.c cor_func.c math_func.c
FILES = check_cor.c corewar.c get_parameters.c main_cycle.c debug_func.c get_int.c output_text.c $(FUNCS)
# FILES = main.c
OBJS = $(FILES:.c=.o)

ifeq ($(shell uname), Linux)
	ESCAPE := \033
	CC = clang
else
	ESCAPE := \x1b
	CC = gcc
endif

all: $(NAME)

# WTF
# Change that shit! (If u can)
$(NAME): $(addprefix $(ODIR), $(OBJS)) $(LIB)
	@echo "$(ESCAPE)[34m\nCompiling $@$(ESCAPE)[0m"
	@$(CC) $(CFLAGS) -I $(IDIR) -I $(LDIR)includes -o $@ $^

g:
	@echo "$(ESCAPE)[34m\nCompiling debug $(NAME)$(ESCAPE)[0m"
	@$(MAKE) --no-print-directory -C $(LDIR) g
	@$(CC) $(CFLAGS) -g -I $(IDIR) -I $(LDIR)includes -o $(NAME) $(addprefix $(SDIR), $(FILES)) $(LDIR)dlibft.a

$(LIB):
	@echo "$(ESCAPE)[35m\nCompiling $(notdir $@)$(ESCAPE)[0m"
	@$(MAKE) --no-print-directory -C $(dir $@) $(notdir $@)
	@echo "$(ESCAPE)[35m\n$(notdir $@) compiled$(ESCAPE)[0m"

$(addprefix $(ODIR), %.o): $(addprefix $(SDIR), %.c)
	@printf "."
	@$(CC) $(CFLAGS) -I $(IDIR) -I $(LDIR)includes -c -o $@ $<

r: $(NAME)
	./$(NAME)
	#parameters

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
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory
