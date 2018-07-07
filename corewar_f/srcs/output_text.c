/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 12:57:08 by bcherkas          #+#    #+#             */
/*   Updated: 2018/07/07 16:07:43 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	printline(unsigned char *map, int line, int max)
{
	int		i;

	i = 0;
	while (i < max)
	{
		ft_printf("%.2hhx ", map[line * max + i]);
		i++;
	}
	ft_printf("\n");
}

static void	output_sd(t_info *inf, unsigned char *map, int mode)
{
	int			i;
	char		*str;

	str = NULL;
	i = 1;
	ft_printf("0x0000 : ");
	printline(inf->map, 0, 64);
	while (i < 64)
	{
		ft_printf("%#6.4x : ", i * 64);
		printline(map, i, 64);
		i++;
	}
	if (mode)
	{
		if (get_next_line(0, &str) > 0)
			free(str);
		if (str == NULL)
		{
			ft_lstdel(&inf->stack, free);
			exit(0);
		}
	}
}

static void	output_dump(t_info *inf, unsigned char *map)
{
	int			i;

	i = 1;
	ft_printf("0x0000 : ");
	printline(inf->map, 0, 32);
	while (i < 128)
	{
		ft_printf("%#6.4x : ", i * 32);
		printline(map, i, 32);
		i++;
	}
	ft_lstdel(&inf->stack, free);
	exit(0);
}

void		print_v_16(unsigned char *map, int start, int ende)
{
	const int	end = ende > start ? ende : 4096 + ende;
	const int	res = end - start;
	int			i;

	if (start == end)
		return ;
	i = 0;
	ft_printf("ADV %d (0x%.4x -> 0x%.4x)", res, start, end);
	while (i < res)
	{
		ft_printf("%3.2hx", map[(start + i) % MEM_SIZE]);
		i++;
	}
	write(1, " \n", 2);
}

void		output_text(t_info *inf, int cycles)
{
	if (inf->args[FLAG_DUMP] > -1 && cycles == inf->args[FLAG_DUMP])
		output_dump(inf, inf->map);
	if (inf->args[FLAG_S] > 0 && cycles % inf->args[FLAG_S] == 0 && cycles > 0)
		output_sd(inf, inf->map, 1);
	if ((inf->args[FLAG_D] > -1 && cycles == inf->args[FLAG_D]) || !cycles)
	{
		output_sd(inf, inf->map, 0);
		ft_lstdel(&(inf->stack), free);
		exit(0);
	}
}
