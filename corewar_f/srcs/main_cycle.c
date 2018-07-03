/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 18:51:41 by bcherkas          #+#    #+#             */
/*   Updated: 2018/07/03 20:56:23 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** g_op_tab:
** 1. function pointer, 2.number of cycles it need, 3. arguments it can have
** 5. can have codage  6. label size
*/

static const t_op	g_op_tab[MAX_FUNC] =
{
	{cor_live, 10, {T_DIR, 0, 0}, 0, 4},
	{cor_ld, 5, {T_DIR | T_IND, T_REG, 0}, 1, 4},
	{cor_st, 5, {T_REG, T_IND | T_REG, 0}, 1, 4},
	{cor_add, 10, {T_REG, T_REG, T_REG}, 1, 4},
	{cor_sub, 10, {T_REG, T_REG, T_REG}, 1, 4},
	{cor_and, 6, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
	{cor_or, 6, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
	{cor_xor, 6, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
	{cor_zjmp, 20, {T_DIR, 0, 0}, 0, 2},
	{cor_ldi, 25, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
	{cor_sti, 25, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 1, 2},
	{cor_fork, 800, {T_DIR, 0, 0}, 0, 2},
	{cor_lld, 10, {T_DIR | T_IND, T_REG, 0}, 1, 4},
	{cor_lldi, 50, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
	{cor_lfork, 1000, {T_DIR, 0, 0}, 0, 2},
	{cor_aff, 2, {T_REG, 0, 0}, 1, 4}
};

int		check_args(int **cod, int **args, unsigned char *map, t_carriage *car)
{
	int			i;
	int			*codage;
	const int	func_num = map[car->pc] - 1;
	int			ret;

	ret = 0;
	i = 0;
	codage = get_codage(map[car->pc + 1], g_op_tab[func_num].codage);
	while (i < 3)
	{
		if ((codage[i] & g_op_tab[func_num].codage[i]) != codage[i])
			ret = 1;
		else if (codage[i] == 0 && g_op_tab[func_num].codage[i] != 0)
			ret = 1;
		i++;
	}
	*cod = codage;
	if (ret == 1)
		return (1);
	*args = get_args(map, car->pc + 2, codage, g_op_tab[func_num].lab);
	if (args == NULL)
		return (1);
	return (0);
}

void	function_trigger(t_carriage *carry, unsigned char *map, int func_num)
{
	const int		old_pc = carry->pc;
	const int		save = get_args_flag(NULL, FLAG_V);
	int				*codage;
	int				*args;

	codage = NULL;
	args = NULL;
	carry->cycles_left = 0;
	if (g_op_tab[func_num].cod_oct > 0)
	{
		if (check_args(&codage, &args, map, carry))
		{
			carry->pc = (carry->pc + 2 + codage[0] + codage[1] + codage[2])
				% MEM_SIZE;
			if (save > -1 && (save & 16) == 16)
				print_v_16(map, old_pc, carry->pc);
			return ;
		}
		carry->func(map, carry, codage, args);
	}
	else
		carry->func(map, carry);
	if (save > -1 && (save & 16) == 16 && map[old_pc] != 9)
		print_v_16(map, old_pc, carry->pc);
}

void	wrapper(unsigned char *map, t_carriage *carry)
{
	int		func_num;

	func_num = map[carry->pc];
	ncur_print_carry(carry, func_num, 1);
	if (carry->cycles_left > 1)
		carry->cycles_left--;
	else if (carry->cycles_left == 0 && (func_num > MAX_FUNC || func_num < 1))
	{
		ncur_print_carry(carry, func_num, 0);
		carry->pc = (carry->pc + 1) % MEM_SIZE;
	}
	else if (carry->cycles_left == 0 && func_num <= MAX_FUNC && func_num > 0)
	{
		carry->func = g_op_tab[func_num - 1].func;
		carry->cycles_left = g_op_tab[func_num - 1].cycles - 1;
	}
	else if (carry->cycles_left == 1 && func_num <= MAX_FUNC && func_num > 0)
	{
		ncur_print_carry(carry, func_num, 0);
		function_trigger(carry, map, func_num - 1);
		ncur_print_carry(carry, map[carry->pc], 1);
	}
	carry->cycles_without_live++;
}

void	help_me(t_info *inf, int iterations, int *cycles)
{
	if (*cycles == inf->cycles_to_die)
	{
		cycle_to_die_func(inf, iterations);
		*cycles = 0;
	}
	if (inf->output_mode == 1 || inf->output_mode == 2)
		output_text(inf, iterations);
	(*cycles)++;
}

void	main_cycle(t_info *inf)
{
	int			save;
	t_list		*lst;
	int			iterations;
	int			cycles;

	save = inf->args[FLAG_V] > 0 && (inf->args[FLAG_V] & 2) == 2 ? 1 : 0;
	cycles = 1;
	iterations = 0;
	while (42)
	{
		if (inf->args[FLAG_N] == 1)
			ncurses_trigger(inf, iterations);
		inf->carriages = 0;
		iterations++;
		lst = inf->stack;
		if (save > 0)
			ft_printf("It is now cycle %d\n", iterations);
		while (lst)
		{
			wrapper(inf->map, (t_carriage *)lst->content);
			lst = lst->next;
			(inf->carriages)++;
		}
		help_me(inf, iterations, &cycles);
	}
}
