/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 18:33:20 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/16 17:39:14 by bcherkas         ###   ########.fr       */
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

int		*get_args(unsigned char *map, int st, int *cod, int label_s)
{
	static int	args[3];
	int			i;
	int			*ret;

	i = 0;
	ret = args;
	while (i < 3)
	{
		if (cod[i] == T_REG)
			if ((args[i] = get_reg(map, st)) < 0)
				ret = NULL;
		if (cod[i] == T_IND)
			args[i] = get_ind(map, st);
		else if (cod[i] == T_DIR)
		{
			args[i] = get_dir(map, st, label_s);
			cod[i] = label_s;
		}
		else if (cod[i] != T_DIR && cod[i] != T_IND && cod[i] != T_REG)
			args[i] = 0;
		st += cod[i];
		i++;
	}
	return (ret);
}
