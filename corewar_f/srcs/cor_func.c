/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:11:22 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/12 19:39:59 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "corewar.h"

void	cor_aff(unsigned char *map, t_carriage *carry, int *codage, int *args)
{
	int		flag;
	
	if (map && codage)
		;
	flag = get_args_flag(NULL, FLAG_A);
	if (flag == 1)
		ft_printf("%c\n", args[0] % 256);
	else if (flag == 2)
		ft_printf("%#8.6x\n", args[0]);
	carry->pc = (carry->pc + 3) % MEM_SIZE;
}

void	cor_zjmp(unsigned char *map, t_carriage *carry)
{
	int		i;

	if (carry->carry == 0)
		return ;
	i = get_dir(map, carry->pc + 1, 2) % IDX_MOD;
	carry->pc = (MEM_SIZE + carry->pc + i) % MEM_SIZE;
}

void	cor_live(unsigned char *map, t_carriage *carry)
{
	t_header	*player;
	int			player_number;
	int			flag;

	player = NULL;
	flag = get_args_flag(NULL, FLAG_V);
	carry->lives++;
	player_number = get_dir(map, carry->pc + 1, 4);
	player_number = PLAYER_CODE - player_number;
	if (player_number >= 0 && player_number < carry->players_amount)
	{
		player = get_player_info(NULL, player_number);
		carry->players[player_number]++;
		if ((flag & 1) == 1)
			ft_printf("Player \"%s\" with number %d is alive!\n", player->prog_name, player_number);
	}
	carry->pc = (carry->pc + 5) % MEM_SIZE;
}
