/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:57:01 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/13 16:24:19 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	introduce(t_info *inf)
{
	int		i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < inf->players_amount)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			i + 1, inf->head[i].prog_size,
			inf->head[i].prog_name, inf->head[i].comment);
		i++;
	}
}

void	winner(t_info *inf)
{
	int		i;

	i = 0;
	while (i < inf->players_amount)
	{
		if (inf->last_dead == &(inf->head[i]))
			break ;
		i++;
	}
	ft_printf("Contestant %d, \"%s\", has won !\n", i + 1,
			inf->last_dead->prog_name);
}
