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

void		new_carriage(t_list **add_pointer, t_list *lst)
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

int			get_args_flag(int *args, int flag)
{
	static int	*args_arr;

	if (args == NULL)
		return (args_arr[flag]);
	args_arr = args;
	return (0);
}

t_header	*get_player_info(t_header *arr, int player)
{
	static t_header	*players_arr;

	if (arr == NULL)
	{
		players_arr = arr;
		return (NULL);
	}
	if (player > 3 || player < 0)
		return (NULL);
	return (&(players_arr[player]));
}
