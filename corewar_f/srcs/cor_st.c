/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_st.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 17:16:57 by astadnik          #+#    #+#             */
/*   Updated: 2018/06/09 17:44:35 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cor_st(unsigned char *map, t_carriage *carry)
{
	int	codage[3];
	int	args[3];

	get_args(map, carry->pc + 1, args, codage);
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

void	cor_sti(unsigned char *map, t_carriage *carry)
{
	int	codage[3];
	int	args[3];
	int	val1;
	int	val2;

	get_args(map, carry->pc + 1, args, codage);
	val1 = 0;
	val2 = 0;// Silence errors, change later
	if (codage[1] == 1)
		val1 = carry->reg[args[1]];
	else if (codage[1] == 2)
		val1 = get_ind(map, carry->pc + args[1] % IDX_MOD);
	else if (codage[1] == 4)
		val1 = args[1];
	else
		errmsg("Wrong codage");
	if (codage[2] == 1)
		val2 = carry->reg[args[2]];
	else if (codage[2] == 4)
		val2 = args[2];
	else
		errmsg("Wrong codage");
	map[(carry->pc + (val1 + val2) % IDX_MOD) % MEM_SIZE] =
		(unsigned char)carry->reg[args[0]];
}
