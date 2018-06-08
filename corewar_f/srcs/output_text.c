/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 12:57:08 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/08 13:33:52 by bcherkas         ###   ########.fr       */
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

static void	output_sd(t_info *inf, unsigned char *map)
{
	t_header	*head;
	int			i;

	head = inf->head;
	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < inf->players_amount)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", 
			i, head[i].prog_size, head[i].prog_name, head[i].comment);
		i++;
	}
	i = 1;
	ft_printf("0x0000 : ");
	printline(map, 0);
	while (i < 64)
	{
		ft_printf("%#6.4x : ", i * 64);
		printline(map, i);
		i++;
	}
}

void		output_text(t_info *inf, int iterations)
{
	char		*str;

	str = NULL;
	if (inf->args[FLAG_S] > 0 && iterations % inf->args[FLAG_S] == 0)
	{
		output_sd(inf, inf->map);
		if (get_next_line(0, &str) > 0)
			free(str);
	}
	if (inf->args[FLAG_D] > 0 && iterations % inf->args[FLAG_D] == 0)
	{
		output_sd(inf, inf->map);
		ft_lstdel(&(inf->stack), free);
		exit(0);
	}
}