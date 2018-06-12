/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 18:26:29 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/12 20:41:22 by bcherkas         ###   ########.fr       */
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

void		print_v_16(unsigned char *map, int start, int end)
{
	if (start && end)
		ft_printf("ADV %d (%#6.4x -> %#6.4x)", end - start + 1, start, end + 1);
	else if (start == 0 && end)
		ft_printf("ADV %d (0x0000 -> %#6.4x)", end - start + 1, end + 1);
	else if (end == 0 && start)
		ft_printf("ADV %d (%#6.4x -> 0x0000)", end - start + 1, start);
	if (end < start)
		end = MEM_SIZE + end;
	while (start < end)
	{
		ft_printf("%3.2hhx", map[start % MEM_SIZE]);
		start++;
	}
	ft_printf("%3.2hhx\n", map[start % MEM_SIZE]);
}
