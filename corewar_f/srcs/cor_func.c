/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:11:22 by bcherkas          #+#    #+#             */
/*   Updated: 2018/07/02 19:22:50 by bcherkas         ###   ########.fr       */
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
	int			i;

	if (carry->carry == 1)
	{
		i = get_dir(map, carry->pc + 1, 2) % IDX_MOD;
		carry->pc = (MEM_SIZE + carry->pc + i) % MEM_SIZE;
	}
	if (flag > 0 && (flag & 4) == 4)
		ft_printf("P%5d | zjmp %d %s\n", carry->number, i,
				i == 0 ? "FAILED" : "OK");
}

void	cor_live(unsigned char *map, t_carriage *carry)
{
	int			save;
	t_header	*player;
	int			player_number;
	const int	flag = get_args_flag(NULL, FLAG_V);

	player = NULL;
	carry->lives++;
	save = get_dir(map, carry->pc + 1, 4);
	player_number = PLAYER_CODE - save;
	if (player_number >= 0 && player_number < carry->players_amount)
	{
		player = get_player_info(NULL, player_number);
		carry->players[player_number]++;
		if (flag > 0 && (flag & 1) == 1)
			ft_printf("Player %d (%s) is said to be alive\n",
					player_number + 1, player->prog_name);
	}
	carry->cycles_without_live = 0;
	carry->pc = (carry->pc + 5) % MEM_SIZE;
	if (flag > 0 && (flag & 4) == 4)
		ft_printf("P%5d | live %d\n", carry->number, save);
}
