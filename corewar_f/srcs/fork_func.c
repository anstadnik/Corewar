/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 16:55:34 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/07 17:59:06 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	new_carriage(t_list **add_pointer, t_list *lst)
{
	static t_list	**start;

	if (lst)
	{
		ft_lstadd(start, lst);
		return ;
	}
	if (add_pointer)
	{
		start = add_pointer;
		return ;
	}
}

void	cor_fork(unsigned char *map, t_carriage *carry)
{
	short int	pc;
	t_list		*lst;
	t_carriage	*new;

	lst = ft_lstnew(carry, sizeof(t_carriage));
	new = (t_carriage *)lst->content;
	pc = (short)(((short)map[carry->pc + 1]) << 8) + (short)map[carry->pc + 2]; 
	new->pc = (new->pc + (pc % IDX_MOD)) % MEM_SIZE;
	new_carriage(NULL, lst);
	ft_printf("%hd + %hd = %hd\n", pc, carry->pc, new->pc);
	carry->pc = (carry->pc + 3) % MEM_SIZE;
}
