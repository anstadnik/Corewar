/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 16:55:34 by bcherkas          #+#    #+#             */
/*   Updated: 2018/07/06 20:41:48 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cor_fork(unsigned char *map, t_carriage *carry)
{
	const int	flag = get_args_flag(NULL, FLAG_V);
	const int	pc = get_short(map, carry->pc + 1);
	t_list		*lst;
	t_carriage	*new;

	lst = ft_lstnew(carry, sizeof(t_carriage));
	new = (t_carriage *)lst->content;
	new->pc = new->pc + pc % IDX_MOD;
	if (flag > 0 && (flag & 4) == 4)
		ft_printf("P %4d | fork %d (%d)\n", carry->number, pc, new->pc);
	new->pc = (MEM_SIZE + new->pc) % MEM_SIZE;
	new_carriage(NULL, lst);
	carry->pc = (carry->pc + 3) % MEM_SIZE;
	if (get_args_flag(NULL, FLAG_N) == 1)
		ncur_print_carry(new, map[new->pc], 1);
}

void	cor_lfork(unsigned char *map, t_carriage *carry)
{
	const int	flag = get_args_flag(NULL, FLAG_V);
	const int	pc = get_short(map, carry->pc + 1);
	t_list		*lst;
	t_carriage	*new;

	lst = ft_lstnew(carry, sizeof(t_carriage));
	new = (t_carriage *)lst->content;
	new->pc = new->pc + pc;
	if (flag > 0 && (flag & 4) == 4)
		ft_printf("P %4d | lfork %d (%d)\n", carry->number, pc, new->pc);
	new->pc = (MEM_SIZE + new->pc) % MEM_SIZE;
	new_carriage(NULL, lst);
	carry->pc = (carry->pc + 3) % MEM_SIZE;
	if (get_args_flag(NULL, FLAG_N) == 1)
		ncur_print_carry(new, map[new->pc], 1);
}
