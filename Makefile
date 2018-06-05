.PHONY: all check clean fclean re d kappa rekappa

NAME=test

CC=gcc -Wall -Wextra -Werror

INCLUDES=-I./includes -I./libft

SRC=corewar.c check_cor.c get_parameters.c

SRCS=$(addprefix ./srcs/, $(SRC))

OBJ=$(SRCS:.c=.o)

LIBFT=./libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(INCLUDES) -o $@ $^
	@echo "lem-in compiled"

d: fclean
	$(CC) $(INCLUDES) -g -o $(NAME) $(SRCS) ./libft/*.c

check: 
	@true

$(LIBFT): check
	@$(MAKE) -C ./libft
	@echo "libft compiled"

%.o: %.c
	@$(CC) $(INCLUDES) -c -o $@ $<

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C ./libft clean
	@echo "cleaned"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C ./libft fclean
	@echo "fcleaned"

re: fclean all
