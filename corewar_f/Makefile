.PHONY: clean fclean re r g
CFLAGS = -Wall -Wextra -Werror -Wconversion#remove last one
ODIR = objs/
SDIR = srcs/
IDIR = includes/
LDIR = ../libft/
NAME = corewar
LIB = $(LDIR)libft.a
FUNCS = fork_func.c cor_func.c math_func.c bit_funcs.c st_func.c ld_func.c
HELP = get_int.c help_functions.c live_functions.c get_args.c sort_players.c
OUTPUT = output_text.c final_output.c ncurses.c ncurses_help.c ncurses_trigger.c
FILES = check_cor.c corewar.c get_parameters.c main_cycle.c $(FUNCS) $(HELP) $(OUTPUT)
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
	@$(CC) $(CFLAGS) -I $(IDIR) -I $(LDIR)includes -o $@ $^ -lncurses

g:
	@echo "$(ESCAPE)[34m\nCompiling debug $(NAME)$(ESCAPE)[0m"
	@$(MAKE) --no-print-directory -C $(LDIR) g
	@$(CC) $(CFLAGS) -g -I $(IDIR) -I $(LDIR)includes -o $(NAME) $(addprefix $(SDIR), $(FILES)) $(LDIR)dlibft.a -lncurses

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
