/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 18:26:29 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/08 18:36:26 by bcherkas         ###   ########.fr       */
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
	ft_lstdel(start, free);
}
