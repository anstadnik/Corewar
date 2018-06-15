/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 18:26:29 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/15 17:07:26 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		new_carriage(t_list **add_pointer, t_list *lst)
{
	static t_list	**start;
	t_carriage		*tmp;
	t_carriage		*tmp2;

	if (lst)
	{
		tmp = (t_carriage *)(*start)->content;
		tmp2 = (t_carriage *)lst->content;
		tmp2->number = tmp->number + 1;
		tmp2->cycles_left = 0;
		ft_lstadd(start, lst);
		return ;
	}
	if (add_pointer)
	{
		start = add_pointer;
		return ;
	}
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

	if (arr != NULL)
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
	if (start == end)
		return ;
	if (start && end)
		ft_printf("ADV %d (%#6.4x -> %#6.4x)", ABS(end - start), start, end);
	else if (start == 0 && end)
		ft_printf("ADV %d (0x0000 -> %#6.4x)", ABS(end - start), end);
	else if (end == 0 && start)
		ft_printf("ADV %d (%#6.4x -> 0x0000)", ABS(end - start), start);
	if (end < start)
		end = MEM_SIZE + end;
	if (map)
		;
	while (start < end)
	{
		ft_printf("%3.2hx", map[start % MEM_SIZE]);
		start++;
	}
	write(1, " \n", 2);
}

void		swap_union_mgc(t_magic *kek)
{
	unsigned char	c;

	c = kek->arr[0];
	kek->arr[0] = kek->arr[3];
	kek->arr[3] = c;
	c = kek->arr[1];
	kek->arr[1] = kek->arr[2];
	kek->arr[2] = c;
}
