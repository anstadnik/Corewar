/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 13:40:35 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/12 19:40:28 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cor_add(unsigned char *map, t_carriage *carry, int *codage, int *args)
{
	if (map && codage)
		;
	carry->reg[args[2]] = carry->reg[args[0]] + carry->reg[args[1]];
	carry->carry = carry->reg[args[2]] == 0 ? 1 : 0;
	carry->pc = (carry->pc + 5) % MEM_SIZE;
}

void	cor_sub(unsigned char *map, t_carriage *carry, int *codage, int *args)
{
	if (map && codage)
		;
	carry->reg[args[2]] = carry->reg[args[0]] - carry->reg[args[1]];
	carry->carry = carry->reg[args[2]] == 0 ? 1 : 0;
	carry->pc = (carry->pc + 5) % MEM_SIZE;
}
