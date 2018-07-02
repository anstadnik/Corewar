/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 12:08:16 by bcherkas          #+#    #+#             */
/*   Updated: 2018/07/02 19:19:38 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			get_int(unsigned char *map, int pc)
{
	t_magic	mgc;

	pc = (MEM_SIZE + pc) % MEM_SIZE;
	mgc.arr[0] = map[(pc + 3) % MEM_SIZE];
	mgc.arr[1] = map[(pc + 2) % MEM_SIZE];
	mgc.arr[2] = map[(pc + 1) % MEM_SIZE];
	mgc.arr[3] = map[(pc) % MEM_SIZE];
	return (mgc.magic);
}

int			get_short(unsigned char *map, int pc)
{
	t_magic		mgc;
	short		sh;

	pc = (MEM_SIZE + pc) % MEM_SIZE;
	mgc.arr[0] = map[(pc + 1) % MEM_SIZE];
	mgc.arr[1] = map[pc % MEM_SIZE];
	mgc.arr[2] = 0;
	mgc.arr[3] = 0;
	sh = (short)mgc.magic;
	mgc.magic = sh;
	return (mgc.magic);
}

int			get_ind(unsigned char *map, int pc)
{
	int		ret;
	int		pc2;

	pc2 = get_short(map, pc);
	ret = get_int(map, pc2);
	return (ret);
}

int			get_dir(unsigned char *map, int pc, int len)
{
	int		ret;

	if (len == 2)
		ret = get_short(map, pc);
	else
		ret = get_int(map, pc);
	return (ret);
}

int			get_reg(unsigned char *map, int pc)
{
	int		ret;

	pc = (MEM_SIZE + pc) % MEM_SIZE;
	ret = map[pc];
	if (ret < 1 || ret > 16)
		return (-1);
	return (ret - 1);
}
