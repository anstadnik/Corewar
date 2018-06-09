/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:11:22 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/09 11:50:18 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "corewar.h"

void	cor_aff(unsigned char *map, t_carriage *carry, ssize_t flag)
{
	int		point;
	
	point = get_reg(map, carry->pc + 2);
	if (flag == 1)
		ft_printf("%c\n", map[point] % 256);
	else if (flag == 2)
		ft_printf("%#8.6x\n", map[point]);
	carry->pc = (carry->pc + 3) % MEM_SIZE;
	carry->cycles_left--;
}

void	cor_zjmp(unsigned char *map, t_carriage *carry)
{
	int		i;

	if (carry->carry == 0)
		return ;
	i = get_dir(map, carry->pc + 1, 2) % IDX_MOD;
	ft_printf("OLD: %d\n", carry->pc);
	carry->pc = (MEM_SIZE + carry->pc + i) % MEM_SIZE;
	ft_printf("NEW: %d\n", carry->pc);
}

void	cor_live(unsigned char *map, t_carriage *carry)
{
	int	player_number;

	carry->lives++;
	player_number = get_dir(map, carry->pc+1, 4);
	if (player_number >= 0 && player_number < carry->players_amount)
		carry->players[player_number]++;
}
