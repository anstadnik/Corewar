/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_ld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 11:54:36 by astadnik          #+#    #+#             */
/*   Updated: 2018/06/15 18:27:13 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cor_ld(unsigned char *map, t_carriage *carry, int *codage, int *args)
{
	if (args && map)
	{
		if (codage[0] == T_IND)
		{
			args[0] = (get_short(map, carry->pc + 2) % IDX_MOD) + carry->pc;
			args[0] = get_int(map, args[0]);
		}
		carry->reg[args[1]] = args[0];
		carry->carry = carry->reg[args[1]] ? 0 : 1;
	}
	carry->pc = (carry->pc + codage[0] + codage[1] + 2) % MEM_SIZE;
}

void	cor_lld(unsigned char *map, t_carriage *carry, int *codage, int *args)
{
	if (args)
	{
		if (codage[0] == T_IND)
		{
			args[0] = get_short(map, carry->pc + 2) + carry->pc;
			args[0] = get_int(map, args[0]);
		}
		carry->reg[args[1]] = args[0];
		carry->carry = carry->reg[args[1]] ? 0 : 1;
	}
	carry->pc = (carry->pc + codage[0] + codage[1] + 2) % MEM_SIZE;
}

void	cor_ldi(unsigned char *map, t_carriage *carry, int *codage, int *args)
{
	int		pc2;

	pc2 = 0;
	if (args)
	{
		if (codage[0] == T_REG)
			args[0] = carry->reg[args[0]];
		if (codage[0] == T_IND)
		{
			args[0] = (get_short(map, carry->pc + 2) % IDX_MOD) + carry->pc;
			args[0] = get_int(map, args[0]);
		}
		if (codage[1] == T_REG)
			args[1] = carry->reg[args[1]];
		pc2 = get_dir(map, (carry->pc + args[0] + args[1]) % IDX_MOD, 4);
		carry->reg[args[2]] = pc2;
		carry->carry = carry->reg[args[2]] ? 0 : 1;
	}
	carry->pc = (carry->pc + codage[0] + codage[1] + codage[2] + 2) % MEM_SIZE;
}

void	cor_lldi(unsigned char *map, t_carriage *carry, int *codage, int *args)
{
	int		pc2;

	pc2 = 0;
	if (args)
	{
		if (codage[0] == T_REG)
			args[0] = carry->reg[args[0]];
		if (codage[0] == T_IND)
		{
			args[0] = (get_short(map, carry->pc + 2) % IDX_MOD) + carry->pc;
			args[0] = get_int(map, args[0]);
		}
		if (codage[1] == T_REG)
			args[1] = carry->reg[args[1]];
		pc2 = get_dir(map, (carry->pc + args[0] + args[1]), 4);
		carry->reg[args[2]] = pc2;
		carry->carry = carry->reg[args[2]] ? 0 : 1;
	}
	carry->pc = (carry->pc + codage[0] + codage[1] + codage[2] + 2) % MEM_SIZE;

}
