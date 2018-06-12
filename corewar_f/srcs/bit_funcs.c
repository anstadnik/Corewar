/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 18:33:20 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/12 20:20:42 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		*get_codage(unsigned char code)
{
	int			i;
	static int	codage[3];

	codage[0] = (int)((code >> 6) & 3);
	codage[1] = (int)((code >> 4) & 3);
	codage[2] = (int)((code >> 2) & 3);
	if ((code & 3) > 0)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		if (codage[i] == REG_CODE)
			codage[i] = T_REG;
		else if (codage[i] == IND_CODE)
			codage[i] = T_IND;
		else if (codage[i] == DIR_CODE)
			codage[i] = T_DIR;
		else
			codage[i] = 0;
		i++;
	}
	return (codage);
}

int		*get_args(unsigned char *map, int st, int *codage, int label_s)
{
	static int	args[3];
	int			i;

	i = 0;
	while (i < 3)
	{
		if (codage[i] == T_REG)
		{
			if ((args[i] = get_reg(map, st)) < 0)
				return (NULL);
		}
		else if (codage[i] == T_IND)
			args[i] = get_ind(map, st);
		else if (codage[i] == T_DIR)
		{
			args[i] = label_s > 2 ? get_dir(map, st, 4) : get_dir(map, st, 2);
			codage[i] = label_s;
		}
		else
			args[i] = 0;
		st += codage[i];
		i++;
	}
	return (args);
}

void	cor_and(unsigned char *map, t_carriage *carry, int *codage, int *args)
{
	if (map && codage)
		;
	if (codage[0] == T_REG)
		args[0] = carry->reg[args[0]];
	if (codage[1] == T_REG)
		args[1] = carry->reg[args[1]];
	carry->reg[args[2]] = args[0] & args[1];
	carry->carry = carry->reg[args[2]] == 0 ? 1 : 0;
	carry->pc = (carry->pc + 2 + codage[0] + codage[1] + codage[2]) % MEM_SIZE;
}

void	cor_or(unsigned char *map, t_carriage *carry, int *codage, int *args)
{
	if (map && codage)
		;
	if (codage[0] == T_REG)
		args[0] = carry->reg[args[0]];
	if (codage[1] == T_REG)
		args[1] = carry->reg[args[1]];
	carry->reg[args[2]] = args[0] | args[1];
	carry->carry = carry->reg[args[2]] == 0 ? 1 : 0;
	carry->pc = (carry->pc + 2 + codage[0] + codage[1] + codage[2]) % MEM_SIZE;
}

void	cor_xor(unsigned char *map, t_carriage *carry, int *codage, int *args)
{
	if (map && codage)
		;
	if (codage[0] == T_REG)
		args[0] = carry->reg[args[0]];
	if (codage[1] == T_REG)
		args[1] = carry->reg[args[1]];
	carry->reg[args[2]] = args[0] ^ args[1];
	carry->carry = carry->reg[args[2]] == 0 ? 1 : 0;
	carry->pc = (carry->pc + 2 + codage[0] + codage[1] + codage[2]) % MEM_SIZE;
}
