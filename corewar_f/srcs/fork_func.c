/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 16:55:34 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/13 16:57:22 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cor_fork(unsigned char *map, t_carriage *carry)
{
	short int	pc;
	t_list		*lst;
	t_carriage	*new;

	lst = ft_lstnew(carry, sizeof(t_carriage));
	new = (t_carriage *)lst->content;
	pc = get_short(map, carry->pc + 1) % IDX_MOD;
	new->pc = (MEM_SIZE + new->pc + pc) % MEM_SIZE;
	new->cycles_left = 0;
	new_carriage(NULL, lst);
	carry->pc = (carry->pc + 3) % MEM_SIZE;
}

void	cor_lfork(unsigned char *map, t_carriage *carry)
{
	short int	pc;
	t_list		*lst;
	t_carriage	*new;

	lst = ft_lstnew(carry, sizeof(t_carriage));
	new = (t_carriage *)lst->content;
	pc = get_short(map, carry->pc + 1);
	new->pc = (MEM_SIZE + new->pc + pc) % MEM_SIZE;
	new->cycles_left = 0;
	new_carriage(NULL, lst);
	carry->pc = (carry->pc + 3) % MEM_SIZE;
}
