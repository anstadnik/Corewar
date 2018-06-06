/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:41:35 by lburlach          #+#    #+#             */
/*   Updated: 2018/06/06 19:09:47 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int ac, char **av)
{
	header_t	magic_structure;
	int			fd;

	if (ac == 1)
		usage();
	else if (ac > 2)
		error_ac(av[ac - 1]);
	fd = open(av[ac - 1], O_RDONLY);
	//error if fd == -1 ?
	parse_name_and_comment(fd, &magic_structure);
	return (0);
}
