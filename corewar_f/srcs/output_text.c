/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 12:57:08 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/13 18:47:04 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "corewar.h"

static void	printline(unsigned char *map, int line)
{
	int		i;

	i = 0;
	while (i < 64)
	{
		ft_printf("%3.2hhx", map[line * 64 + i]);
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
	printline(inf->map, 0);
	while (i < 64)
	{
		ft_printf("%#6.4x : ", i * 64);
		printline(map, i);
		i++;
	}
	if (mode == 1)
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

void		output_binary(t_info *inf)
{
	unsigned char	map[MEM_SIZE];
	int				i;

	if (inf->args[FLAG_B] == 1)
	{
		write(1, inf->map, MEM_SIZE);
		write(1, "\n", 1);
		return ;
	}
	i = 0;
	while (i < MEM_SIZE)
	{
		if (inf->map[i])
			map[i] = 0xFF;
		else
			map[i] = 0;
		i++;
	}
	write(1, map, MEM_SIZE);
	write(1, "\n", 1);
}

void		output_text(t_info *inf, int cycles)
{
	if (cycles > 0)
	{
		if (inf->args[FLAG_B] > 0)
			output_binary(inf);
		else if (inf->args[FLAG_S] > 0 && cycles % inf->args[FLAG_S] == 0)
			output_sd(inf, inf->map, 1);
	}
	if ((inf->args[FLAG_D] > -1 && cycles == inf->args[FLAG_D]) || !cycles)
	{
		output_sd(inf, inf->map, 2);
		ft_lstdel(&(inf->stack), free);
		exit(0);
	}
}