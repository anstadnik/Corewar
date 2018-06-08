/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 16:55:34 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/08 12:49:39 by bcherkas         ###   ########.fr       */
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
	pc = get_short(map, carry->pc) % IDX_MOD;
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
	pc = get_short(map, carry->pc);
	new->pc = (MEM_SIZE + new->pc + pc) % MEM_SIZE;
	new->cycles_left = 0;
	new_carriage(NULL, lst);
	carry->pc = (carry->pc + 3) % MEM_SIZE;
}
