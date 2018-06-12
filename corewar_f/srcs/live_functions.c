/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 17:10:29 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/12 19:43:00 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_lives(t_info *inf)
{
	t_list		*ptr;
	t_carriage	*carriage;
	int			i;
	int			alives;

	ptr = inf->stack;
	while (ptr)
	{
		carriage = ptr->content;
		if (carriage->lives > 0)
			carriage->lives = 0; // OK
		else if (!carriage->lives)
			carriage->lives = -1; // No live for 1 cycle_to_die, hm
		else if (carriage->lives == -1)
			ft_lstdelnode(&inf->stack, ptr); // No live for 2 cycle_to_die, EXTERMINATUS
		// TODO What happens if there r no carriages?
	}
	i = inf->players_amount;
	alives = 0;
	while (i--)
	{
		inf->players[i] = inf->players[i] > 0 ? 0 : -1; // If 0 or -1 we make it -1
		//which means he's dead
		//which we gotta check in live function
		alives += inf->players[i] == 0;
	}
	// There r alive players and carriages
}
