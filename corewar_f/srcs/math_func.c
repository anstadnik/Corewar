/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 13:40:35 by bcherkas          #+#    #+#             */
/*   Updated: 2018/07/06 16:48:34 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cor_add(unsigned char *map, t_carriage *carry, int *codage, int *args)
{
	const int	flag = get_args_flag(NULL, FLAG_V);

	if (map && codage && args)
	{
		carry->reg[args[2]] = carry->reg[args[0]] + carry->reg[args[1]];
		carry->carry = carry->reg[args[2]] == 0 ? 1 : 0;
		if (flag > 0 && (flag & 4) == 4)
			ft_printf("P %4d | add r%d r%d r%d\n", carry->number,
					args[0] + 1, args[1] + 1, args[2] + 1);
	}
	carry->pc = (carry->pc + 5) % MEM_SIZE;
}

void	cor_sub(unsigned char *map, t_carriage *carry, int *codage, int *args)
{
	const int	flag = get_args_flag(NULL, FLAG_V);

	if (map && codage && args)
	{
		carry->reg[args[2]] = carry->reg[args[0]] - carry->reg[args[1]];
		carry->carry = carry->reg[args[2]] == 0 ? 1 : 0;
		if (flag > 0 && (flag & 4) == 4)
			ft_printf("P %4d | sub r%d r%d r%d\n", carry->number,
					args[0] + 1, args[1] + 1, args[2] + 1);
	}
	carry->pc = (carry->pc + 5) % MEM_SIZE;
}
