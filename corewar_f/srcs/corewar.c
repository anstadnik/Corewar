/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 13:59:51 by bcherkas          #+#    #+#             */
/*   Updated: 2018/07/08 17:18:01 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		usage(void)
{
	ft_printf("Usage: ./corewar [-d N -s N -v N --dump N | --ncurses] ");
	ft_printf("[-a | -A] [-n N] <champ1.cor> <...>\n");
	USAGE("-n     : Sets players number");
	USAGE("-a     : Prints output from \"aff\" (prints char)");
	USAGE("-A     : Prints output from \"aff\" (prints hexadecimal value)");
	ft_printf("#### TEXT OUTPUT MODE ######################################\n");
	USAGE("-d     : Dumps memory after N cycles and exits. 64 bytes per line");
	USAGE("--dump : Dumps memory after N cycles and exits. 32 bytes per line");
	USAGE("-s     : Dumps memory every N cycles. 64 bytes per line");
	USAGE("-v     : Verbosity levels, can be added together to enable several");
	USAGE_VERB("- 1  : Show lives");
	USAGE_VERB("- 2  : Show cycles");
	USAGE_VERB("- 4  : Show operations");
	USAGE_VERB("- 8  : Show deaths");
	USAGE_VERB("- 16 : Show PC movements (Except for jumps)");
	ft_printf("#### NCURSES MODE ##########################################\n");
	ft_printf("     --ncurses : Ncurses output mode\n");
	ft_printf("############################################################\n");
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
	SET_ARR(inf->players, 0);
	while (i < 7)
	{
		inf->args[i] = -1;
		i++;
	}
	inf->winner = NULL;
	add_lives(inf, 0);
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
	new_carriage(inf, NULL);
	get_player_info(inf->head, 0);
}

int			main(int argc, char **argv)
{
	t_info	inf;

	if (argc < 2)
		usage();
	if (argc > MAX_ARGS_NUMBER)
		return (errmsg("Too many arguments"));
	initialize(&inf);
	get_parameters(argc - 1, argv + 1, &inf);
	if (inf.players_amount < 1)
		errmsg("Too few players");
	if (inf.args[FLAG_N] == 1)
		ncur_init_window(&inf);
	read_players(&inf);
	init_map(&inf);
	if (inf.args[FLAG_N] != 1)
		introduce(&inf);
	if (inf.args[FLAG_D] == 0)
		output_text(&inf, 0);
	inf.lives = 0;
	main_cycle(&inf);
}
