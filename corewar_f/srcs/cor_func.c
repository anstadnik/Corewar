/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:11:22 by bcherkas          #+#    #+#             */
/*   Updated: 2018/07/07 13:34:46 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cor_aff(unsigned char *map, t_carriage *carry, int *codage, int *args)
{
	int		flag;

	if (map && codage && args)
	{
		flag = get_args_flag(NULL, FLAG_A);
		if (flag == 1)
			ft_printf("%c\n", carry->reg[args[0]] % 256);
		else if (flag == 2)
			ft_printf("%#8.6x\n", carry->reg[args[0]]);
	}
	carry->pc = (carry->pc + 3) % MEM_SIZE;
}

void	cor_zjmp(unsigned char *map, t_carriage *carry)
{
	const int	flag = get_args_flag(NULL, FLAG_V);
	const int	i = get_short(map, carry->pc + 1);

	if (carry->carry == 1)
	{
		if (get_args_flag(NULL, FLAG_N) == 1)
			ncur_print_carry(carry, map[carry->pc], 0);
		carry->pc = (MEM_SIZE + carry->pc + (i % IDX_MOD)) % MEM_SIZE;
		if (get_args_flag(NULL, FLAG_N) == 1)
			ncur_print_carry(carry, map[carry->pc], 1);
	}
	if (flag > 0 && (flag & 4) == 4)
		ft_printf("P %4d | zjmp %d %s\n", carry->number, i,
				carry->carry == 0 ? "FAILED" : "OK");
	if (carry->carry == 0)
	{
		if (flag > 0 && (flag & 16) == 16)
			print_v_16(map, carry->pc, (carry->pc + 3));
		carry->pc = (carry->pc + 3) % MEM_SIZE;
	}
}

void	cor_live(unsigned char *map, t_carriage *carry)
{
	const int	save = get_dir(map, carry->pc + 1, 4);
	t_header	*player;
	int			player_number;
	const int	flag = get_args_flag(NULL, FLAG_V);

	player = NULL;
	carry->lives++;
	player_number = PLAYER_CODE - save;
	if (flag > 0 && (flag & 4) == 4)
		ft_printf("P %4d | live %d\n", carry->number, save);
	if (player_number >= 0 && player_number < carry->players_amount)
	{
		player = get_player_info(NULL, player_number);
		carry->players[player_number]++;
		set_winner(NULL, player_number);
		if (flag > 0 && (flag & 1) == 1)
			ft_printf("Player %d (%s) is said to be alive\n",
					player_number + 1, player->prog_name);
	}
	carry->cycles_without_live = 0;
	carry->pc = (carry->pc + 5) % MEM_SIZE;
}
