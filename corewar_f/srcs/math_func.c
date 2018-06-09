/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 13:40:35 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/09 11:57:16 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cor_add(unsigned char *map, t_carriage *carry)
{
	int		ind1;
	int		ind2;
	int		ind3;

	// Why there is codage in this func?
	ind1 = get_reg(map, carry->pc + 2);
	ind2 = get_reg(map, carry->pc + 3);
	ind3 = get_reg(map, carry->pc + 4);
	carry->reg[ind3] = carry->reg[ind1] + carry->reg[ind2];
	carry->carry = carry->reg[ind3] == 0 ? 1 : 0;
	carry->pc = (carry->pc + 5) % MEM_SIZE;
}

void	cor_sub(unsigned char *map, t_carriage *carry)
{
	int		ind1;
	int		ind2;
	int		ind3;

	ind1 = get_reg(map, carry->pc + 2);
	ind2 = get_reg(map, carry->pc + 3);
	ind3 = get_reg(map, carry->pc + 4);
	carry->reg[ind3] = carry->reg[ind1] - carry->reg[ind2];
	carry->carry = carry->reg[ind3] == 0 ? 1 : 0;
	carry->pc = (carry->pc + 5) % MEM_SIZE;
}
