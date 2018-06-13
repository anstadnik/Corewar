/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 12:08:16 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/13 17:18:14 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "corewar.h"

int			get_int(unsigned char *map, int pc)
{
	int		i;
	t_magic	mgc;

	i = 0;
	while (i < 4)
	{
		mgc.arr[i] = map[(pc + i) % MEM_SIZE];
		i++;
	}
	return (mgc.magic);
}

short int	get_short(unsigned char *map, int pc)
{
	short int	ret;
	short int	i1;
	short int	i2;

	i1 = map[(pc) % MEM_SIZE];
	i2 = map[(pc + 1) % MEM_SIZE];
	ret = (short)(((short)i1 << 8) + i2);
	return (ret);
}

int			get_ind(unsigned char *map, int pc)
{
	int		ret;
	short	pc2;

	pc2 = (MEM_SIZE + get_short(map, pc)) % MEM_SIZE;
	ret = get_int(map, pc2);
	return (ret);
}

int			get_dir(unsigned char *map, int pc, int len)
{
	int		ret;
	short	help;

	if (len == 2)
	{
		help = get_short(map, pc);
		ret = help;
	}
	else
		ret = get_int(map, pc);
	return (ret);
}

int			get_reg(unsigned char *map, int pc)
{
	int		ret;

	ret = map[pc];
	if (ret < 1 || ret > 16)
		return (-1);
	return (ret - 1);
}
