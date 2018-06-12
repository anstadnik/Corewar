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
	if (codage[1] == 1)
		carry->reg[args[1]] = carry->reg[args[0]];
	if (codage[1] == 2)
		// TODO check if it writes 1 byte or all 4
		// There must be memcpy to write 4 bytes, if i dont mistake
		map[(carry->pc + args[1] % IDX_MOD) % MEM_SIZE] =
			(unsigned char)carry->reg[args[0]];
	else
		errmsg("Wrong codage");
}

void	cor_sti(unsigned char *map, t_carriage *carry, int *codage, int *args)
{
	t_magic	mgc;
	int		start;

	if (codage[1] == T_REG)
		args[1] = carry->reg[args[1]];
	if (codage[2] == T_REG)
		args[2] = carry->reg[args[2]];
	mgc.magic = (unsigned int)carry->reg[args[0]];
	start = (carry->pc + (args[1] + args[2]) % IDX_MOD) % MEM_SIZE;
	ft_memcpy(mgc.arr, map + start, 4);
}
