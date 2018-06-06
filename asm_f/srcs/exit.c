/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:56:00 by lburlach          #+#    #+#             */
/*   Updated: 2018/06/06 16:03:27 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	error_asm(char *err, size_t y, size_t x, char *code)
{

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
	exit (1);
}
