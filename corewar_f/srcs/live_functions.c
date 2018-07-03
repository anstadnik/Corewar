/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 17:10:29 by bcherkas          #+#    #+#             */
/*   Updated: 2018/07/03 21:22:13 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	dead_end(t_info *inf, int iterations)
{
	const int	flag_v = get_args_flag(NULL, FLAG_V);
	t_list		*lst;
	t_list		*tmp;
	t_carriage	*car;

	lst = inf->stack;
	if (flag_v > 0 && (flag_v & 2) == 2)
		ft_printf("It is now cycle %d\n", iterations + 1);
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
	inf->stack = NULL;
	stop_ncurses(inf);
	winner(inf);
	exit(0);
}

void	check_carriage_lives(t_info *inf)
{
	const int	flag_v = get_args_flag(NULL, FLAG_V);
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
			ft_lstdelnode(&inf->stack, tmp);
			if (flag_v > 0 && (flag_v & 8) == 8)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				car->number, car->cycles_without_live - 1, inf->cycles_to_die);
		}
	}
	if (inf->stack == NULL)
		winner(inf);
}

void	check_players_lives(t_info *inf, int *check_lives)
{
	int			i;

	i = inf->players_amount - 1;
	while (i >= 0)
	{
		*check_lives = *check_lives > inf->players[i] ?
			*check_lives : inf->players[i];
		if (inf->players[i] > 0)
			inf->players[i] = 0;
		else if (inf->players[i] == 0)
		{
			inf->players[i] = -1;
			inf->last_dead = &(inf->head[i]);
		}
		i--;
	}
}

void	cycle_to_die_check(t_info *inf, int check_lives)
{
	static int	checks;

	if (check_lives >= NBR_LIVE)
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

void	cycle_to_die_func(t_info *inf, int iterations)
{
	const int	flag_v = get_args_flag(NULL, FLAG_V);
	int			save;
	int			i;
	int			check_lives;

	save = inf->cycles_to_die;
	check_lives = get_max_lives(inf);
	check_carriage_lives(inf);
	check_players_lives(inf, &check_lives);
	cycle_to_die_check(inf, check_lives);
	i = inf->players_amount;
	if (flag_v > 0 && (flag_v & 2) == 2 && save != inf->cycles_to_die)
		ft_printf("Cycle to die is now %d\n", inf->cycles_to_die);
	if (inf->cycles_to_die <= 0)
	{
		while (i >= 0)
		{
			if (inf->players[i] > -1)
				inf->last_dead = &(inf->head[i]);
			i--;
		}
		dead_end(inf, iterations);
	}
}
