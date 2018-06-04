/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 18:11:13 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/04 19:37:31 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		open_file(int fd)
{
	t_magic	uni;
	int		i;
	char	c;

	if (read(fd, &i, 0) < 0)
		errmsg("It is not .cor file");
	i = 0;
	while (i < 4)
	{
		if (read(fd, &uni.arr[3 - i], 1) == 0)
			errmsg("Wrong file");
		i++;
	}
	if (uni.magic != COREWAR_EXEC_MAGIC)
		errmsg("Wrong file");
	return (1);
}

int		check_file(int fd, t_header *head)
{
	char	str[4];

	open_file(fd);
	head->prog_name[NAME_LEN] = 0;
	if (read(fd, head->prog_name, NAME_LEN) < NAME_LEN)
		errmsg("Wrong file");
	if (read(fd, str, 4) < 4 || ft_memcmp(str, "\0\0\0\0", 4))
		errmsg("Wrong file");
	if (read(fd, head->prog_name, NAME_LEN) < NAME_LEN)
		errmsg("Wrong file");	
	if (read(fd, &head->prog_size, 4) < 4)
		errmsg("Wrong file");
	ft_printf("%d\n", head->prog_size);
	return (1);
}
