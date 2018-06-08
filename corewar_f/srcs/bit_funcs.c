/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 18:33:20 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/08 20:12:32 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	get_codage(unsigned char code, int *codage)
{
	int		i;

	i = 0;
	ft_printf("%b\n", code);
	codage[0] = (int)((code >> 4) & 3);
	codage[1] = (int)((code >> 2) & 3);
	codage[2] = (int)(code & 3);
	ft_printf("KEK: %d %d %d\n", codage[0], codage[1], codage[2]);
	while (i < 3)
	{
		if (codage[i] == T_REG)
			codage[i] = 1;
		if (codage[i] == T_IND)
			codage[i] = 2;
		if (codage[i] == T_DIR)
			codage[i] = 4;
		i++;
	}
}

void	get_args(unsigned char *map, int start, int *args, int *codage)
{
	int		i;

	i = 0;
	get_codage(map[start], codage);
	start++;
	while (i < 3)
	{
		if (codage[i] == 1)
			args[i] = get_reg(map, start);
		else if (codage[i] == 2)
			args[i] = get_ind(map, start);
		else if (codage[i] == 4)
			args[i] = get_dir(map, start, 4);
		start += codage[i];
		i++;
		ft_printf("ARG %d = %d\n", i, args[i]);
	}
}

void	cor_and(unsigned char *map, t_carriage *carry)
{
	int		codage[3];
	int		args[3];

	get_args(map, carry->pc + 1, args, codage);
	if (codage[0] == 1)
		args[0] = carry->reg[args[0]];
	if (codage[1] == 1)
		args[1] = carry->reg[args[1]];
	carry->reg[args[2]] = args[0] & args[1];
	ft_printf("AA\n");
	carry->carry = carry->reg[args[2]] == 0 ? 1 : 0;
	carry->pc = (carry->pc + 2 + codage[0] + codage[1] + codage[2]) % MEM_SIZE;
}

void	cor_or(unsigned char *map, t_carriage *carry)
{
	int		codage[3];
	int		args[3];

	get_args(map, carry->pc + 1, args, codage);
	if (codage[0] == 1)
		args[0] = carry->reg[args[0]];
	if (codage[1] == 1)
		args[1] = carry->reg[args[1]];
	carry->reg[args[2]] = args[0] | args[1];
	carry->carry = carry->reg[args[2]] == 0 ? 1 : 0;
	carry->pc = (carry->pc + 2 + codage[0] + codage[1] + codage[2]) % MEM_SIZE;
}

void	cor_xor(unsigned char *map, t_carriage *carry)
{
	int		codage[3];
	int		args[3];

	get_args(map, carry->pc + 1, args, codage);
	if (codage[0] == 1)
		args[0] = carry->reg[args[0]];
	if (codage[1] == 1)
		args[1] = carry->reg[args[1]];
	carry->reg[args[2]] = args[0] ^ args[1];
	carry->carry = carry->reg[args[2]] == 0 ? 1 : 0;
	carry->pc = (carry->pc + 2 + codage[0] + codage[1] + codage[2]) % MEM_SIZE;
}
