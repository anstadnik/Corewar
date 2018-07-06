/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:56:00 by lburlach          #+#    #+#             */
/*   Updated: 2018/07/06 19:50:57 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

const static char	*g_str[] = {
	"Wrong instruction",
	"Can't read the file",
	"The whole name/comment should be encapsulated with \"\"",
	"There should be a whitespace between name command and name itself",
	"You have to close the opening \"",
	"Champ's name should be less than 128 symbols",
	"There should be a whitespace between comment command and comment itself",
	"There can't be a newline between instruction and its name",
	"There's no code in the file",
	"Wrong label",
	"Wrong command",
	"Malloc couldn't allocate memory",
	"There are no command arguments",
	"There's wrong separator",
	"There are some forbidden chars in argument of the command",
	"Invalid number of register(chars)",
	"Invalid reg number!",
	"Invalid number in T_DIR",
	"Invalid number in T_IND",
	"There's some unknown character after first argument",
	"There's some unknown character after second argument",
	"Invalid number of args!"
};

void	error_asm(int err_num, size_t x, char **code, int fd)
{
	if (!code || !(*code))
		ft_printf("{red}%s at [%.3d, %.3d]{eoc}\n",
				g_str[err_num - 1], g_count, x + 1);
	else
		ft_printf("{red}%s at [%.3d, %.3d]:{eoc}\n{light red}%s{eoc}\n",
				g_str[err_num - 1], g_count, x + 1, *code);
	ft_strdel(code);
	close(fd);
	exit(1);
}

void	usage(void)
{
	ft_printf("Usage: ./asm [-a] <sourcefile.s>\n"
"    -a : Instead of creating a .cor file, outputs a stripped and annotated "
					"version of the code to the standard output\n");
	exit(1);
}
