/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 18:48:09 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/06 20:10:21 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	printmap(unsigned char *map)
{
	int		i;

	i = 1;
	while (i <= MEM_SIZE)
	{
		if (map[i - 1])
			printf("\x1b[32m");
		printf("%3.2hhx", map[i - 1]);
			printf("\x1b[0m");
		if (i % 64 == 0)
			printf("\n");
		i++;
	}
}

void	print_stack(t_list *tmp)
{
	while (tmp)
	{
		ft_printf("%d\n", ((t_carriage *)tmp->content)->map_start);
		tmp = tmp->next;
	}
}
