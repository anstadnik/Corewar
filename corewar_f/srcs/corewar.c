/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 13:59:51 by bcherkas          #+#    #+#             */
/*   Updated: 2018/07/03 18:49:12 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			errmsg(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit(0);
}

void		initialize(t_info *inf)
{
	int		i;

	i = 0;
	inf->stack = NULL;
	inf->players_amount = 0;
	inf->cycles_to_die = CYCLE_TO_DIE;
	ft_bzero(inf->map, MEM_SIZE);
	while (i < 6)
	{
		inf->args[i] = -1;
		i++;
	}
	inf->last_dead = NULL;
	get_args_flag(inf->args, 0);
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
	tmp.lives = 0;
	while (j < REG_NUMBER)
	{
		tmp.reg[j] = 0;
		j++;
	}
	tmp.reg[0] = (PLAYER_CODE - player);
	tmp.number = player + 1;
	tmp.cycles_without_live = 0;
	tmp.player_num = player + 1;
	return (tmp);
}

void		init_map(t_info *inf)
{
	t_carriage	tmp;
	t_list		*head;
	int			i;

	i = 0;
	while (i < inf->players_amount)
	{
		inf->players[i] = 0;
		tmp = init_carriage(i, inf->players_amount);
		tmp.players = inf->players;
		tmp.players_amount = inf->players_amount;
		head = ft_lstnew(&tmp, sizeof(tmp));
		ft_lstadd(&inf->stack, head);
		inf->head[i].player_number = i + 1;
		i++;
	}
	while (i < 4)
	{
		inf->players[i] = -1;
		i++;
	}
	inf->carriages = inf->players_amount;
	new_carriage(&(inf->stack), NULL);
	get_player_info(inf->head, 0);
}

int			main(int argc, char **argv)
{
	t_info	inf;

	if (argc < 2 || argc > MAX_ARGS_NUMBER)
		return (errmsg("Too many or too few arguments"));
	initialize(&inf);
	get_parameters(argc - 1, argv + 1, &inf);
	if (inf.args[FLAG_N] == 1)
		ncur_init_window(&inf);
	read_players(&inf);
	init_map(&inf);
	if (inf.args[FLAG_N] != 1)
		introduce(&inf);
	if (inf.args[FLAG_D] == 0)
		output_text(&inf, 0);
	main_cycle(&inf);
}
