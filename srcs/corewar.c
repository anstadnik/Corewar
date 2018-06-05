/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 13:59:51 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/04 19:37:17 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		errmsg(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit (0);
}

void	initialize(t_info *inf)
{
	int		i;

	i = 0;
	inf->start = NULL;
	inf->end = NULL;
	inf->players = 0;
	ft_bzero(inf->map, MEM_SIZE);
	while (i < 6)
	{
		inf->args[i] = -1;
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_info	inf;

	if (argc < 2 || argc > MAX_ARGS_NUMBER)
		return (errmsg("Too many or too few arguments"));
	initialize(&inf);
	get_parameters(argc - 1, argv + 1, &inf);
	read_players(&inf);
}
