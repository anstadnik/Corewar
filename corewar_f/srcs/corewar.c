/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 13:59:51 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/07 18:15:15 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		errmsg(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit (0);
}

void	initialize(t_info *inf)
{
	int		i;

	i = 0;
	inf->stack = NULL;
	inf->players = 0;
	inf->cycles_to_die = CYCLE_TO_DIE;
	ft_bzero(inf->map, MEM_SIZE);
	while (i < 6)
	{
		inf->args[i] = -1;
		i++;
	}
}

t_carriage	init_carriage(int player, int max)
{
	t_carriage	tmp;

	int			j;

	j = 1;
	tmp.carry = 0;
	tmp.pc = (MEM_SIZE / max) * player;
	tmp.map_start = tmp.pc;
	tmp.cycles_left = 0;
	while (j < REG_NUMBER)
	{
		tmp.reg[j] = 0;
		j++;
	}
	tmp.reg[0] = (unsigned)(PLAYER_CODE - player);
	return (tmp);
}

void	init_map(t_info *inf)
{
	t_carriage	tmp;
	t_list		*head;
	int			i;

	i = 0;
	inf->carriage_number = inf->players;
	while (i < inf->players)
	{
		tmp = init_carriage(i, inf->players);
		head = ft_lstnew(&tmp, sizeof(tmp));
		ft_lstadd(&inf->stack, head);
		i++;
	}
	new_carriage(&(inf->stack), NULL);
}
}

int		main(int argc, char **argv)
{
	t_info	inf;

	if (argc < 2 || argc > MAX_ARGS_NUMBER)
		return (errmsg("Too many or too few arguments"));
	initialize(&inf);
	get_parameters(argc - 1, argv + 1, &inf);
	read_players(&inf);
	init_map(&inf);
//	printmap(inf.map);
	main_cycle(&inf, inf.map);
	//print_stack(t_list *tmp);
	ft_lstdel(&(inf.stack), free);
}
