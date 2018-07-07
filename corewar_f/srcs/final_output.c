/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:57:01 by bcherkas          #+#    #+#             */
/*   Updated: 2018/07/07 16:23:05 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	introduce(t_info *inf)
{
	int		i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < inf->players_amount)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			i + 1, inf->head[i].prog_size,
			inf->head[i].prog_name, inf->head[i].comment);
		i++;
	}
}

void	winner(t_info *inf)
{
	int		i;

	i = 0;
	stop_ncurses(inf);
	if (!inf->winner)
		inf->winner = &(inf->head[inf->players_amount - 1]);
	ft_printf("Contestant %d, \"%s\", has won !\n",
			inf->winner->player_number, inf->winner->prog_name);
	exit(0);
}

void	*ft_memcpy_cor(void *str1, size_t start, const void *str2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < n)
	{
		j = (start + i) % MEM_SIZE;
		((char *)str1)[j] = ((char *)str2)[i];
		i++;
	}
	return (str1);
}

int		alldead(t_info *inf)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if (inf->players[i] > -1)
			return (0);
		i++;
	}
	return (1);
}

int			errmsg(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit(0);
}
