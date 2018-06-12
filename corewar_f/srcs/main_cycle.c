/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 18:51:41 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/12 20:54:13 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "corewar.h"

/*
** g_op_tab:
** 1. function pointer, 2.number of cycles it need, 3. arguments it can have
** 4. can have codage  5. label size
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

int		check_args(int **cod, int **ags, unsigned char *map, t_carriage *car)
{
	int		i;
	int		*codage;
	int		*args;
	int		func_num;

	func_num = map[car->pc] - 1;
	i = 0;
	if (!(codage = get_codage(map[car->pc + 1])))
		return (1);
	while (i < 3)
	{
		if ((codage[i] & g_op_tab[func_num].codage[i]) != codage[i])
			return (1);
		i++;
	}
	args = get_args(map, car->pc + 2, codage, g_op_tab[func_num].lab);
	if (args == NULL)
		return (1);
	*ags = args;
	*cod = codage;
	return (0);
}

void	function_trigger(t_carriage *carry, unsigned char *map, int func_num)
{
	int				old_pc;
	int				*codage;
	int				*args;

	codage = NULL;
	args = NULL;
	old_pc = carry->pc;
	if (g_op_tab[func_num].cod_oct > 0)
	{
		if (check_args(&codage, &args, map, carry))
		{
			carry->pc = (carry->pc + 2) % MEM_SIZE;
			if ((get_args_flag(NULL, FLAG_V) & 16) == 16)
				print_v_16(map, old_pc, carry->pc - 1);
			return ;
		}
		carry->func(map, carry, codage, args);
	}
	else
		carry->func(map, carry);
	if ((get_args_flag(NULL, FLAG_V) & 16) == 16 && map[old_pc] != 8)
		print_v_16(map, old_pc, carry->pc - 1);
	carry->cycles_left--;
}

void	wrapper(unsigned char *map, t_carriage *carry)
{
	int		func_num;

	func_num = map[carry->pc];
	if (carry->cycles_left > 1)
		carry->cycles_left--;
	else if (carry->cycles_left == 0 && (func_num > MAX_FUNC || func_num < 1))
		carry->pc = (carry->pc + 1) % MEM_SIZE;
	else if (carry->cycles_left == 0 && func_num <= MAX_FUNC && func_num > 0)
	{
		carry->func = g_op_tab[func_num - 1].func;
		carry->cycles_left = g_op_tab[func_num - 1].cycles;
	}
	else if (carry->cycles_left == 1 && func_num <= MAX_FUNC && func_num > 0)
		function_trigger(carry, map, func_num - 1);
}

void	main_cycle(t_info *inf)
{
	t_list	*lst;
	int		iterations;

	iterations = 0;
	while (42)
	{
		lst = inf->stack;
		if (lst == NULL || inf->cycles_to_die <= 0)
			return ;
		while (lst)
		{
			wrapper(inf->map, (t_carriage *)lst->content);
			lst = lst->next;
		}
		if (inf->output_mode == 1 || inf->output_mode == 2)
			output_text(inf, iterations);
		if (iterations + 1 % CYCLE_TO_DIE == 0)
			check_lives(inf);
		iterations++;
	}
}
