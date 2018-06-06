/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:56:00 by lburlach          #+#    #+#             */
/*   Updated: 2018/06/06 20:44:28 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

const static char 	*g_str[] = {
		"There's no '.name' field",
		"There's no '.comment' field",
		"Wrong instruction",
		"Can't read the file"
};

void	error_asm(int err_num, size_t x, char *code)
{
	if (x == 0)
		ft_printf("{red}%s at %d row:{eoc}\n\t{light red}%s{eoc}\n",
				g_str[err_num - 1], g_count, code);
	else
		ft_printf("{red}%s at [%.3d, %.3d]:{eoc}\n\t{light red}%s{eoc}\n",
				g_str[err_num - 1], g_count, x, code);
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
