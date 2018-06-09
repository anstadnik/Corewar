/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_ld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 11:54:36 by astadnik          #+#    #+#             */
/*   Updated: 2018/06/09 16:45:37 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cor_ld(unsigned char *map, t_carriage *carry)
{
	int	codage[3];
	int	args[3];
	int	val;

	get_args(map, carry->pc + 1, args, codage);
	if (codage[0] == 4)
		val = args[0];
	if (codage[0] == 2)
		val = get_ind(map, carry->pc + args[0] % IDX_MOD);
	if (args[1] < REG_NUMBER)// TODO Is it a correct behavior?
		carry->reg[args[1]] = val;
	carry->carry = val ? 0 : 1;
}

void	cor_ldi(unsigned char *map, t_carriage *carry)
{
	int	codage[3];
	int	args[3];
	int	val1;
	int	val2;

	get_args(map, carry->pc + 1, args, codage);
	val1 = 0;
	val2 = 0;// Silence errors, change later
	if (codage[0] == 1)
		val1 = carry->reg[args[0]];
	else if (codage[0] == 2)
		val1 = get_ind(map, carry->pc + args[0] % IDX_MOD);
	else if (codage[0] == 4)
		val1 = args[0];
	else
		errmsg("Wrong codage");
	if (codage[1] == 1)
		val2 = carry->reg[args[1]];
	else if (codage[1] == 4)
		val2 = args[1];
	else
		errmsg("Wrong codage");
	carry->reg[args[2]] = get_ind(map, (val1 + val2) % IDX_MOD + carry->pc);
}

void	cor_lld(unsigned char *map, t_carriage *carry)
{
	int	codage[3];
	int	args[3];
	int	val;

	get_args(map, carry->pc + 1, args, codage);
	if (codage[0] == 4)
		val = args[0];
	if (codage[0] == 2)
		val = get_ind(map, carry->pc + args[0]);
	if (args[1] < REG_NUMBER)// TODO Is it a correct behavior?
		carry->reg[args[1]] = val;
	carry->carry = val ? 0 : 1;
}

// Check if I should remove both IDX_MODES, or only one
void	cor_lldi(unsigned char *map, t_carriage *carry)
{
	int	codage[3];
	int	args[3];
	int	val1;
	int	val2;

	get_args(map, carry->pc + 1, args, codage);
	val1 = 0;
	val2 = 0;// Silence errors, change later
	if (codage[0] == 1)
		val1 = carry->reg[args[0]];
	else if (codage[0] == 2)
		val1 = get_ind(map, carry->pc + args[0]);
	else if (codage[0] == 4)
		val1 = args[0];
	else
		errmsg("Wrong codage");
	if (codage[1] == 1)
		val2 = carry->reg[args[1]];
	else if (codage[1] == 4)
		val2 = args[1];
	else
		errmsg("Wrong codage");
	carry->reg[args[2]] = get_ind(map, (val1 + val2) + carry->pc);
}
