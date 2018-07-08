/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncur_init_window.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 16:09:49 by bcherkas          #+#    #+#             */
/*   Updated: 2018/07/02 18:31:19 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	fill_window(WINDOW *win)
{
	int		i;

	i = 0;
	wattron(win, A_DIM);
	while (i < 4096)
	{
		mvwprintw(win, 1 + (i / 64), 2 + 3 * (i % 64), "%.2hhx", 0);
		i++;
	}
	wattroff(win, A_DIM);
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
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
}

void	ncur_init_window(t_info *inf)
{
	t_win	*win;

	win = &(inf->win);
	initscr();
	noecho();
	curs_set(0);
	timeout(0);
	create_colors();
	create_windows(inf);
	get_active_window(0, win->main, win->info);
	wtimeout(win->main, 0);
	wtimeout(win->info, 0);
	win->pause = 1;
	win->iter_per_sec = 50;
	win->speed = 1000000 / 50;
}
