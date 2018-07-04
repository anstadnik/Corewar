/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_ld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 11:54:36 by astadnik          #+#    #+#             */
/*   Updated: 2018/07/04 19:15:26 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		cor_ld(unsigned char *map,
			t_carriage *carry, int *codage, int *args)
{
	const int	flag = get_args_flag(NULL, FLAG_V);

	if (args && map)
	{
		if (codage[0] == T_IND)
		{
			args[0] = (get_short(map, carry->pc + 2) % IDX_MOD) + carry->pc;
			args[0] = get_int(map, args[0]);
		}
		carry->reg[args[1]] = args[0];
		carry->carry = carry->reg[args[1]] ? 0 : 1;
		if (flag > 0 && (flag & 4) == 4)
			ft_printf("P%5d | ld %d r%d\n", carry->number,
					args[0], args[1] + 1);
	}
	carry->pc = (carry->pc + codage[0] + codage[1] + 2) % MEM_SIZE;
}

void		cor_lld(unsigned char *map,
			t_carriage *carry, int *codage, int *args)
{
	const int	flag = get_args_flag(NULL, FLAG_V);

	if (args)
	{
		if (codage[0] == T_IND)
		{
			args[0] = get_short(map, carry->pc + 2) + carry->pc;
			args[0] = get_short(map, args[0]);
		}
		carry->reg[args[1]] = args[0];
		carry->carry = carry->reg[args[1]] ? 0 : 1;
		if (flag > 0 && (flag & 4) == 4)
			ft_printf("P%5d | lld %d r%d\n", carry->number,
					args[0], args[1] + 1);
	}
	carry->pc = (carry->pc + codage[0] + codage[1] + 2) % MEM_SIZE;
}

static void	print_v4(int *args, t_carriage *carry, int mode)
{
	const int	flag = get_args_flag(NULL, FLAG_V);
	int			sum;

	if (flag > 0 && (flag & 4) == 4)
	{
		sum = args[0] + args[1];
		if (mode)
		{
			ft_printf("P%5d | ldi %d %d r%d\n", carry->number,
					args[0], args[1], args[2] + 1);
			ft_printf("       | -> load from ");
			ft_printf("%d + %d = %d (with pc and mod %d)\n",
				args[0], args[1], sum, (carry->pc + sum));
			return ;
		}
		ft_printf("P%5d | ldi %d %d r%d\n", carry->number,
				args[0], args[1], args[2] + 1);
		ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
		args[0], args[1], sum, sum + carry->pc);
	}
}

void		cor_ldi(unsigned char *map,
			t_carriage *carry, int *codage, int *args)
{
	const int	codage_help = map[carry->pc + 1] >> 6;
	int			pc2;

	pc2 = 0;
	if (args)
	{
		if (codage[0] == T_REG)
			args[0] = carry->reg[args[0]];
		if (codage_help == IND_CODE)
		{
			args[0] = (get_short(map, carry->pc + 2) % IDX_MOD) + carry->pc;
			args[0] = get_int(map, args[0]);
		}
		if (codage[1] == T_REG)
			args[1] = carry->reg[args[1]];
		print_v4(args, carry, 1);
		pc2 = get_dir(map, carry->pc + ((args[0] + args[1]) % IDX_MOD), 4);
		carry->reg[args[2]] = pc2;
		carry->carry = carry->reg[args[2]] ? 0 : 1;
	}
	carry->pc = (carry->pc + codage[0] + codage[1] + codage[2] + 2) % MEM_SIZE;
}

void		cor_lldi(unsigned char *map,
			t_carriage *carry, int *codage, int *args)
{
	const int	codage_help = map[carry->pc + 1] >> 6;
	int			pc2;

	pc2 = 0;
	if (args)
	{
		if (codage[0] == T_REG)
			args[0] = carry->reg[args[0]];
		if (codage_help == IND_CODE)
		{
			args[0] = (get_short(map, carry->pc + 2) % IDX_MOD) + carry->pc;
			args[0] = get_int(map, args[0]);
		}
		if (codage[1] == T_REG)
			args[1] = carry->reg[args[1]];
		pc2 = get_dir(map, (carry->pc + args[0] + args[1]), 4);
		carry->reg[args[2]] = pc2;
		carry->carry = carry->reg[args[2]] ? 0 : 1;
		print_v4(args, carry, 0);
	}
	carry->pc = (carry->pc + codage[0] + codage[1] + codage[2] + 2) % MEM_SIZE;
}
