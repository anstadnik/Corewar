/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_st.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 17:16:57 by astadnik          #+#    #+#             */
/*   Updated: 2018/06/12 20:53:27 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cor_st(unsigned char *map, t_carriage *carry, int *codage, int *args)
{
	t_magic	mgc;
	int		start;

	if (codage[1] == T_REG)
		carry->reg[args[1]] = carry->reg[args[0]];
	else
	{
		mgc.magic = (unsigned int)carry->reg[args[0]];
		start = args[1] % IDX_MOD;
		ft_memcpy(mgc.arr, map + start, 4);
	}
	carry->pc = (carry->pc + 2 + codage[0] + codage[1] + codage[2]) % IDX_MOD;
}

void	cor_sti(unsigned char *map, t_carriage *carry, int *codage, int *args)
{
	t_magic	mgc;
	int		start;

	if (codage[1] == T_REG)
		args[1] = carry->reg[args[1]];
	if (codage[2] == T_REG)
		args[2] = carry->reg[args[2]];
	mgc.magic = (unsigned)carry->reg[args[0]];
	swap_union_mgc(&mgc);
	start = (carry->pc + (args[1] + args[2]) % IDX_MOD) % MEM_SIZE;
	ft_memcpy(map + start, mgc.arr, 4);
	carry->pc = (carry->pc + 2 + codage[0] + codage[1] + codage[2]) % IDX_MOD;
}
