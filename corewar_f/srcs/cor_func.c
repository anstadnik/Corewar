/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:11:22 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/08 15:34:29 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "corewar.h"

void	cor_aff(unsigned char *map, t_carriage *carry)
{
	int		point;

	point = get_reg(map, carry->pc + 2);
	ft_printf("%c\n", point % 256);
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
