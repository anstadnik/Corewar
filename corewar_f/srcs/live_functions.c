/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 17:10:29 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/13 19:24:29 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_carriage_lives(t_info *inf)
{
	const int	save = get_args_flag(NULL, FLAG_V);
	t_list		*ptr;
	t_list		*tmp;
	t_carriage	*carriage;

	ptr = inf->stack;
	while (ptr)
	{
		tmp = ptr;
		carriage = (t_carriage *)ptr->content;
		carriage->lives = carriage->lives > 0 ? 0 : -1;
		ptr = ptr->next;
		if (carriage->lives == -1)
		{
			ft_lstdelnode(&inf->stack, tmp);
			if (save > 0 && (save & 8) == 8)
				ft_printf("Process %d dead\n", carriage->number);
		}
	}
}

int		*check_players_lives(t_info *inf)
{
	int			i;
	static int	lives[4];

	i = inf->players_amount;
	while (i >= 0)
	{
		lives[i] = inf->players[i];
		if (inf->players[i] > 0)
			inf->players[i] = 0;
		else if (inf->players[i] == 0)
		{
			inf->players[i] = -1;
			inf->last_dead = &(inf->head[i]);
		}
		i--;
	}
	return (lives);
}

void	cycle_to_die_check(int *lives, t_info *inf)
{
	int			i;
	static int	checks;
	int			check_lives;

	i = inf->players_amount;
	while (i >= 0)
	{
		check_lives = lives[i] > check_lives ? lives[i] : check_lives;
		i--;
	}
	if (check_lives >= NBR_LIVE)
	{
		checks = 0;
		inf->cycles_to_die -= CYCLE_DELTA;
	}
	else
		checks++;
	if (checks == MAX_CHECKS)
	{
		inf->cycles_to_die -= CYCLE_DELTA;
		checks = 0;
	}
}

void	cycle_to_die_func(t_info *inf)
{
	int			save;
	int			*lives;
	int			i;

	save = inf->cycles_to_die;
	check_carriage_lives(inf);
	lives = check_players_lives(inf);
	cycle_to_die_check(lives, inf);
	i = inf->players_amount;
	if ((inf->args[FLAG_V] & 2) == 2 && save != inf->cycles_to_die)
		ft_printf("Cycle to die is now %d\n", inf->cycles_to_die);
	if (inf->cycles_to_die <= 0)
	{
		while (i >= 0)
		{
			if (inf->players[i] > -1)
				inf->last_dead = &(inf->head[i]);
			i--;
		}
		ft_lstdel(&(inf->stack), free);
	}
}
