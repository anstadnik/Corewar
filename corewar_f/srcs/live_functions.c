/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 17:10:29 by bcherkas          #+#    #+#             */
/*   Updated: 2018/07/08 17:18:22 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	dead_end(t_info *inf)
{
	const int	flag_v = inf->args[FLAG_V];
	t_list		*lst;
	t_list		*tmp;
	t_carriage	*car;

	lst = inf->stack;
	while (lst)
	{
		tmp = lst;
		car = (t_carriage *)tmp->content;
		lst = lst->next;
		if (flag_v > 0 && (flag_v & 8) == 8)
			ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				car->number, car->cycles_without_live, inf->cycles_to_die);
		free(car);
		free(tmp);
	}
	winner(inf);
}

void	check_carriage_lives(t_info *inf)
{
	const int	flag_v = inf->args[FLAG_V];
	t_list		*ptr;
	t_list		*tmp;
	t_carriage	*car;

	ptr = inf->stack;
	while (ptr)
	{
		tmp = ptr;
		car = (t_carriage *)ptr->content;
		car->lives = car->lives > 0 ? 0 : -1;
		ptr = ptr->next;
		if (car->lives == -1)
		{
			ncur_print_carry(tmp->content,
					inf->map[((t_carriage *)tmp->content)->pc], 0);
			if (flag_v > 0 && (flag_v & 8) == 8)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				car->number, car->cycles_without_live, inf->cycles_to_die);
			ft_lstdelnode(&inf->stack, tmp);
		}
	}
}

void	check_players_lives(t_info *inf)
{
	int			lives;
	int			i;

	lives = 0;
	i = 0;
	while (i < inf->players_amount)
	{
		if (inf->players[i] > 0)
			inf->players[i] = 0;
		else if (inf->players[i] == 0)
			inf->players[i] = -1;
		i++;
	}
}

void	cycle_to_die_check(t_info *inf)
{
	static int	checks;

	if (inf->lives >= NBR_LIVE)
	{
		checks = 0;
		inf->cycles_to_die -= CYCLE_DELTA;
	}
	else
		checks++;
	if (checks >= MAX_CHECKS)
	{
		inf->cycles_to_die -= CYCLE_DELTA;
		checks = 0;
	}
}

void	cycle_to_die_func(t_info *inf)
{
	const int	flag_v = get_args_flag(NULL, FLAG_V);
	int			save;
	int			check_lives;

	check_lives = 0;
	save = inf->cycles_to_die;
	check_carriage_lives(inf);
	if (inf->stack == NULL)
		winner(inf);
	check_players_lives(inf);
	cycle_to_die_check(inf);
	inf->lives = 0;
	if (flag_v > 0 && (flag_v & 2) == 2 && save != inf->cycles_to_die)
		ft_printf("Cycle to die is now %d\n", inf->cycles_to_die);
}
