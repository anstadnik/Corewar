/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 18:33:20 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/16 19:57:42 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cor_and(unsigned char *map, t_carriage *carry, int *codage, int *args)
{
	const int	flag = get_args_flag(NULL, FLAG_V);

	if (map && codage && args)
	{
		if (codage[0] == T_REG)
			args[0] = carry->reg[args[0]];
		if (codage[1] == T_REG)
			args[1] = carry->reg[args[1]];
		carry->reg[args[2]] = args[0] & args[1];
		carry->carry = carry->reg[args[2]] == 0 ? 1 : 0;
		if (flag > 0 && (flag & 4) == 4)
			ft_printf("P%5d | and %d %d r%d\n", carry->number,
					args[0], args[1], args[2] + 1);
	}
	carry->pc = (carry->pc + 2 + codage[0] + codage[1] + codage[2]) % MEM_SIZE;
}

void	cor_or(unsigned char *map, t_carriage *carry, int *codage, int *args)
{
	const int	flag = get_args_flag(NULL, FLAG_V);

	if (map && codage && args)
	{
		if (codage[0] == T_REG)
			args[0] = carry->reg[args[0]];
		if (codage[1] == T_REG)
			args[1] = carry->reg[args[1]];
		carry->reg[args[2]] = args[0] | args[1];
		carry->carry = carry->reg[args[2]] == 0 ? 1 : 0;
		if (flag > 0 && (flag & 4) == 4)
			ft_printf("P%5d | or %d %d r%d\n", carry->number,
					args[0], args[1], args[2] + 1);
	}
	carry->pc = (carry->pc + 2 + codage[0] + codage[1] + codage[2]) % MEM_SIZE;
}

void	cor_xor(unsigned char *map, t_carriage *carry, int *codage, int *args)
{
	const int	flag = get_args_flag(NULL, FLAG_V);

	if (map && codage && args)
	{
		if (codage[0] == T_REG)
			args[0] = carry->reg[args[0]];
		if (codage[1] == T_REG)
			args[1] = carry->reg[args[1]];
		carry->reg[args[2]] = args[0] ^ args[1];
		carry->carry = carry->reg[args[2]] == 0 ? 1 : 0;
		if (flag > 0 && (flag & 4) == 4)
			ft_printf("P%5d | xor %d %d r%d\n", args[0], args[1], args[2] + 1);
	}
	carry->pc = (carry->pc + 2 + codage[0] + codage[1] + codage[2]) % MEM_SIZE;
}
