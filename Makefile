.PHONY: clean fclean re copy

FOLDER1 = corewar_f
FOLDER2 = asm_f
FOLDERS = $(FOLDER1) $(FOLDER2)
NAME1 = $(FOLDER1)/corewar
NAME2 = $(FOLDER2)/asm

all: $(NAME1) $(NAME2) copy

copy: $(NAME1) $(NAME2)
	@echo "\x1b[36m\nCopying $(NAME1)\x1b[0m"
	@cp $(NAME1) .
	@echo "\x1b[36m\nCopying $(NAME2)\x1b[0m"
	@cp $(NAME2) .

$(NAME1) $(NAME2):
	@echo "\x1b[36m\nCompiling $@\x1b[0m"
	@$(MAKE) -C $(dir $@)

clean:
	@for lib_dir in $(FOLDERS); do \
		$(MAKE) -C $$lib_dir clean; \
	done

fclean: clean
	@for lib_dir in $(FOLDERS); do \
		$(MAKE) -C $$lib_dir fclean; \
	done
	@echo "\x1b[31mRemoving the $(NAME1) and $(NAME2)\x1b[0m"
	@rm -f $(notdir $(NAME1)) $(notdir $(NAME2))

re: 
	@$(MAKE) fclean
	@$(MAKE) 