/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:57:01 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/15 17:40:17 by bcherkas         ###   ########.fr       */
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
	while (i < inf->players_amount)
	{
		if (inf->last_dead == &(inf->head[i]))
			break ;
		i++;
	}
	ft_printf("Contestant %d, \"%s\", has won !\n", i + 1,
			inf->last_dead->prog_name);
	exit(0);
}

int		get_max_lives(t_info *inf)
{
	t_list		*lst;
	t_carriage	*car;
	int			lives;

	lives = 0;
	lst = inf->stack;
	while (lst)
	{
		car = (t_carriage *)lst->content;
		lives = lives > car->lives ? lives : car->lives;
		lst = lst->next;
	}
	return (lives);
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
