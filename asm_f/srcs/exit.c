/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:56:00 by lburlach          #+#    #+#             */
/*   Updated: 2018/06/09 19:25:14 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

const static char 	*g_str[] = {
		"Wrong instruction",
		"Can't read the file",
		"The whole name/comment should be encapsulated with \"\"",
		"There should be a whitespace between name command and name itself",
		"You have to close the opening \"",
		"Champ's name should be less than 128 symbols",
		"There should be a whitespace between comment command and comment itself",
		"There can't be a newline between instruction and its name"
};

void	error_asm(int err_num, size_t x, char **code)
{
	if (!code || !(*code))
		ft_printf("{red}%s at [%.3d, %.3d]{eoc}\n",
				  g_str[err_num - 1], g_count + 1, x + 1);
	else
		ft_printf("{red}%s at [%.3d, %.3d]:{eoc}\n{light red}%s{eoc}\n",
				  g_str[err_num - 1], g_count + 1, x + 1, *code);

	ft_strdel(code);
	exit(1);
}

void	usage(void)
{
	ft_printf("Usage: ./asm [-a] <sourcefile.s>\n"
					  "    -a : Instead of creating a .cor file, outputs a stripped and annotated version of the code to the standard output\n");
	exit(1);
}

void	error_ac(char *s)
{
	ft_printf("Cant read source file %s\n", s);
	exit(1);
}
