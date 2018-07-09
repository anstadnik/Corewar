.PHONY: clean fclean re copy

FOLDER1 = corewar_f
FOLDER2 = asm_f
FOLDERS = $(FOLDER1) $(FOLDER2)
NAME1 = corewar
NAME2 = asm

ifeq ($(shell uname), Linux)
	ESCAPE := \033
else
	ESCAPE := \x1b
endif

all: $(NAME1) $(NAME2)

$(NAME1) $(NAME2):
	@echo "$(ESCAPE)[36m\nCompiling $@$(ESCAPE)[0m"
	@$(MAKE) --no-print-directory -C $@_f

clean:
	@for lib_dir in $(FOLDERS); do \
		$(MAKE) --no-print-directory -C $$lib_dir clean; \
	done

fclean: clean
	@for lib_dir in $(FOLDERS); do \
		$(MAKE) --no-print-directory -C $$lib_dir fclean; \
	done
	@echo "$(ESCAPE)[31mRemoving the $(NAME1) and $(NAME2)$(ESCAPE)[0m"
	@rm -f $(notdir $(NAME1)) $(notdir $(NAME2))

re:
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory
