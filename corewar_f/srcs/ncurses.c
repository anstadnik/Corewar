/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncur_init_window.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 16:09:49 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/29 20:19:34 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	fill_window(WINDOW *win)
{
	int		i;

	i = 0;
	while (i < 4096)
	{
		mvwprintw(win, 1 + (i / 64), 1 + 3 * (i % 64), "%3.2hhx", 0);
		i++;
	}
}

void	create_windows(t_info *inf)
{
	t_win	*win;

	win = &(inf->win);
	win->main = newwin(66, 195, 1, 1);
	win->info = newwin(66, 50, 1, 196);
	box(win->main, 0, 0);
	box(win->info, 0, 0);
	fill_window(win->main);
}

void	create_colors(void)
{
	if (has_colors() == 0)
	{
		endwin();
		ft_printf("error: {red}This terminal does not support colors\n");
		return ;
	}
	start_color();
	use_default_colors();
	init_pair(1, COLOR_GREEN, COLOR_WHITE);
	init_pair(2, COLOR_RED, COLOR_WHITE);
	init_pair(3, COLOR_BLUE, COLOR_WHITE);
	init_pair(4, COLOR_YELLOW, COLOR_WHITE);
}

void	ncur_init_window(t_info *inf)
{
	t_win	*win;

	win = &(inf->win);
	initscr();
	noecho();
	curs_set(0);
//	timeout(0);
	create_colors();
	create_windows(inf);
	get_active_window(0, win->main, win->info);
}
