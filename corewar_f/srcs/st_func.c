/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_st.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 17:16:57 by astadnik          #+#    #+#             */
/*   Updated: 2018/07/07 19:23:11 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_v4(int *args, t_carriage *carry, int pc)
{
	const int	flag = get_args_flag(NULL, FLAG_V);
	int			sum;

	if (flag > 0 && (flag & 4) == 4)
	{
		sum = args[1] + args[2];
		ft_printf("P %4d | sti r%d %d %d\n",
				carry->number, args[0] + 1, args[1], args[2]);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
			args[1], args[2], sum, (pc + sum % IDX_MOD) % MAX_NUMBER);
	}
}

void		cor_st(unsigned char *map,
			t_carriage *carry, int *codage, int *args)
{
	const int	flag = get_args_flag(NULL, FLAG_V);
	t_magic		mgc;
	size_t		start;

	if (codage[1] == T_REG)
		carry->reg[args[1]] = carry->reg[args[0]];
	else
	{
		args[1] = get_short(map, carry->pc + 3);
		mgc.magic = carry->reg[args[0]];
		swap_union_mgc(&mgc);
		start = (size_t)((MEM_SIZE + (carry->pc + args[1] % IDX_MOD))
				% MEM_SIZE);
		ft_memcpy_cor(map, start, mgc.arr, 4);
		color_output(carry->player_num, mgc.arr, (int)start, 4);
	}
	if (flag > 0 && (flag & 4) == 4)
		ft_printf("P %4d | st r%d %d\n", carry->number,
				args[0] + 1, args[1]);
	carry->pc = (carry->pc + 2 + codage[0] + codage[1]) % MEM_SIZE;
}

void		cor_sti(unsigned char *map,
			t_carriage *carry, int *codage, int *args)
{
	t_magic		mgc;
	size_t		start;
	const int	cod2 = (map[(carry->pc + 1) % MEM_SIZE] >> 4) & 3;

	if (codage[1] == T_REG)
		args[1] = carry->reg[args[1]];
	else if (cod2 == IND_CODE)
		args[1] %= IDX_MOD;
	if (codage[2] == T_REG)
		args[2] = carry->reg[args[2]];
	mgc.magic = carry->reg[args[0]];
	swap_union_mgc(&mgc);
	start = (size_t)((MEM_SIZE + carry->pc + ((args[1] + args[2])
			% IDX_MOD)) % MEM_SIZE);
	ft_memcpy_cor(map, start, mgc.arr, 4);
	color_output(carry->player_num, mgc.arr, (int)start, 4);
	print_v4(args, carry, carry->pc);
	carry->pc = (carry->pc + 2 + codage[0] + codage[1] + codage[2]) % MEM_SIZE;
}
