/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 18:26:29 by bcherkas          #+#    #+#             */
/*   Updated: 2018/07/07 13:42:37 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		new_carriage(t_info *inf, t_list *lst)
{
	static int		carriages_num;
	static t_list	**start;
	t_carriage		*tmp;
	t_carriage		*tmp2;

	if (lst)
	{
		carriages_num++;
		tmp = (t_carriage *)(*start)->content;
		tmp2 = (t_carriage *)lst->content;
		tmp2->number = carriages_num;
		tmp2->cycles_left = 0;
		ft_lstadd(start, lst);
		return ;
	}
	if (inf)
	{
		start = &(inf->stack);
		carriages_num = inf->players_amount;
		return ;
	}
	if (inf == NULL && lst == NULL)
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

	if (arr != NULL)
	{
		players_arr = arr;
		return (NULL);
	}
	if (player > 3 || player < 0)
		return (NULL);
	return (&(players_arr[player]));
}

void		set_winner(t_info *infi, int player_num)
{
	static t_info	*inf;

	if (infi != NULL)
		inf = infi;
	else
		inf->winner = &(inf->head[player_num]);


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
