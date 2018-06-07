/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 18:51:41 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/07 18:17:26 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "corewar.h"

void	cor_aff(unsigned char *map, t_carriage *carry);

/*
** op_tab: 
** 1. functionpointer,           2. number of args,
** 3. code of function,          4. can change carry or no,
** 5. have codage octet or no,   6.number of cycles it need,
** 7. size of label
*/
/*
t_op    op_tab[MAX_FUNCTIONS] =
{
	{cor_live, 1, 0x01, 0, 0, 10, 4},
	{cor_ld, 2, 0x02, 1, 0, 5, 4},
	{cor_st, 2, 0x03, 0, 1, 5, 4},
	{cor_add, 1, 0x04, 1, 1, 10, 4},
	{cor_sub, 1, 0x05, 1, 1, 10, 4},
	{cor_and, 1, 0x06, 1, 1, 6, 4},
	{cor_or, 1, 0x07, 1, 1, 6, 4},
	{cor_xor, 1, 0x08, 1, 1, 6, 4},
	{cor_zjmp, 1, 0x09, 0, 0, 20, 2},
	{cor_ldi, 1, 0x0a, 0, 1, 25, 2},
	{cor_sti, 1, 0x0b, 0, 1, 25, 2},
	{cor_fork, 1, 0x0c, 0, 0, 800, 2},
	{cor_lld, 1, 0x0d, 1, 1, 10, 4},
	{cor_ldi, 1, 0x0e, 1, 1, 50, 2},
	{cor_lldi, 1, 0x0f, 0, 0, 1000, 2},
	{cor_aff, 1, 0x10, 0, 1, 2, 4}
};
*/

t_op    op_tab[MAX_FUNC] =
{
	{NULL, 1, 0, 0, 0, 0, 0},
	{NULL, 1, 0, 0, 0, 0, 0},
	{NULL, 1, 0, 0, 0, 0, 0},
	{NULL, 1, 0, 0, 0, 0, 0},
	{NULL, 1, 0, 0, 0, 0, 0},
	{NULL, 1, 0, 0, 0, 0, 0},
	{NULL, 1, 0, 0, 0, 0, 0},
	{NULL, 1, 0, 0, 0, 0, 0},
	{NULL, 1, 0, 0, 0, 0, 0},
	{NULL, 1, 0, 0, 0, 0, 0},
	{NULL, 1, 0, 0, 0, 0, 0},
	{cor_fork, 1, 0x0c, 0, 0, 800, 2},
	{NULL, 1, 0, 0, 0, 0, 0},
	{NULL, 1, 0, 0, 0, 0, 0},
	{NULL, 1, 0, 0, 0, 0, 0},
	{cor_aff, 1, 0x10, 0, 1, 2, 4}
};

void	cor_aff(unsigned char *map, t_carriage *carry)
{
	int		point;

	point = map[carry->pc + 2];
	if (point < 1 || point > 16)
		errmsg("Bastard\n");
	ft_printf("AFF: %hhx\n", carry->reg[point]);
	ft_printf("POSITION: %u\n", carry->pc);
	carry->pc = (carry->pc + 3) % MEM_SIZE;
	ft_printf("%d\n", carry->cycles_left);
}

void	wrapper(unsigned char *map, t_carriage *carry)
{
	int		func_num;

	func_num = map[carry->pc];
	if (carry->cycles_left > 1)
	{
		carry->cycles_left--;
	}
	if (carry->cycles_left == 0 && func_num <= MAX_FUNC && func_num > 0)
	{
		carry->func = op_tab[func_num - 1].func;
		carry->cycles_left = op_tab[func_num - 1].cycles;
	}
	else if (carry->cycles_left == 0 && (func_num > MAX_FUNC || func_num < 1))
	{
		carry->pc = (carry->pc + 1) % MEM_SIZE;
	}
	else if (carry->cycles_left == 1)
	{
		carry->func(map, carry);
		carry->cycles_left--;
	}
}

void	main_cycle(t_info *inf, unsigned char *map)
{
	t_list	*lst;
	int		iterations;

	iterations = 0;
	while (42)
	{
		lst = inf->stack;
		while (lst)
		{
			wrapper(map, (t_carriage *)lst->content);
			lst = lst->next;
		}
		iterations++;
	}
}
