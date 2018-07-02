/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 20:11:26 by bcherkas          #+#    #+#             */
/*   Updated: 2018/07/02 18:19:23 by bcherkas         ###   ########.fr       */
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
	size_t	i;
	size_t	save;
	WINDOW	*win;

	if (get_args_flag(NULL, FLAG_N) != 1)
		return ;
	i = 0;
	save = 0;
	win = get_active_window(1, NULL, NULL);
	wattron(win, COLOR_PAIR(player));
	while (i < len)
	{
		save = i + (size_t)start;
		mvwprintw(win, 1 + (int)(save / 64),
				2 + 3 * (save % 64), "%.2hhx", str[i]);
		i++;
	}
	wattroff(win, COLOR_PAIR(player));
	wrefresh(win);
}

void	ncur_print_carry(t_carriage *carry, t_win *win, int symbol, int mode)
{
	if (get_args_flag(NULL, FLAG_N) != 1)
		return ;
	if (mode == 1)
		wattron(win->main, A_REVERSE);
	wattron(win->main, COLOR_PAIR(carry->player_num));
	mvwprintw(win->main, 1 + (carry->pc / 64), 2 + 3 * (carry->pc % 64),
			"%.2hhx", symbol);
	wattroff(win->main, COLOR_PAIR(carry->player_num));
	if (mode == 1)
		wattroff(win->main, A_REVERSE);
}
