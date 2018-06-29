/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 20:11:26 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/29 20:36:18 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	stop_ncurses(t_info *inf)
{
	if (inf->args[FLAG_N] != 1)
		return ;
	delwin(inf->win.main);
	delwin(inf->win.info);
	endwin();
}

WINDOW	*get_active_window(int num, WINDOW *main, WINDOW *info)
{
	static WINDOW	*main_w;
	static WINDOW	*info_w;

	if (num == 0 && main && info)
	{
		main_w = main;
		info_w = info;
		return (NULL);
	}
	else if (num == 1)
		return (main_w);
	else if (num == 2)
		return (info_w);
	return (NULL);
}

void	color_output(int player, unsigned char *str, int start, size_t len)
{
	int		i;
	int		save;
	WINDOW	*win;

	i = 0;
	save = 0;
	win = get_active_window(1, NULL, NULL);
	wattron(win, COLOR_PAIR(player + 1));
	while (i < (int)len)
	{
		save = i + start;
		mvwprintw(win, 1 + (save / 64), 1 + 3 * (save % 64), "%3.2hhx", str[i]);
		i++;
	}
	wattroff(win, COLOR_PAIR(player + 1));
	wrefresh(win);
}
