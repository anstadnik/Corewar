/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_trigger.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 15:41:58 by bcherkas          #+#    #+#             */
/*   Updated: 2018/07/06 22:15:26 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <math.h>

static void	player_info(t_info *inf, t_win *win, int start)
{
	int		i;
	int		save;
	int		lives;

	i = 0;
	save = 0;
	while (i < inf->players_amount)
	{
		save = start + i * 3;
		lives = inf->players[i];
		mvwprintw(win->info, save, 2, "Player %d : ", i);
		wattron(win->info, COLOR_PAIR(i + 1));
		mvwprintw(win->info, save, 14, "%s", inf->head[i].prog_name);
		wattroff(win->info, COLOR_PAIR(i + 1));
		mvwprintw(win->info, save + 1, 4, "Current lives : %d        ",
				inf->players[i]);
		i++;
	}
}

static void	write_stats(t_info *inf, t_win *win, int iters)
{
	const char	*str = win->pause == 1 ? "** PAUSED ** " : "** RUNNING **";
	int			i;

	i = 0;
	wattron(win->info, A_BOLD);
	mvwprintw(win->info, 2, 2, "%s", str);
	if (win->speed == 0)
		mvwprintw(win->info, 5, 2, "Without limit!             ");
	else if (win->speed != 0)
		mvwprintw(win->info, 5, 2, "Cycles/second limit : %d   ",
			win->iter_per_sec);
	mvwprintw(win->info, 7, 2, "Cycle: %d    ", iters);
	mvwprintw(win->info, 9, 2, "Processes: %d    ", inf->carriages);
	mvwprintw(win->info, 13, 2, "CYCLE TO DIE: %d    ", inf->cycles_to_die);
	mvwprintw(win->info, 15, 2, "CYCLE DELTA: %d", CYCLE_DELTA);
	mvwprintw(win->info, 17, 2, "NBR LIVE: %d", NBR_LIVE);
	mvwprintw(win->info, 19, 2, "MAX CHECKS: %d", MAX_CHECKS);
	player_info(inf, win, 21);
	wattroff(win->info, A_BOLD);
}

static void	change_speed(t_win *win, int num)
{
	win->iter_per_sec += num;
	if (win->iter_per_sec > 1000)
		win->iter_per_sec = 1000;
	else if (win->iter_per_sec < 1)
		win->iter_per_sec = 1;
	win->speed = (unsigned)(round(1000000.0 / (double)win->iter_per_sec));
}

static int	get_command(t_info *inf)
{
	t_win	*win;
	int		a;

	win = &(inf->win);
	a = wgetch(win->info);
	if (a == 32)
		win->pause = (win->pause == 0) ? 1 : 0;
	else if (a == 113)
		change_speed(win, -10);
	else if (a == 119)
		change_speed(win, -1);
	else if (a == 101)
		change_speed(win, 1);
	else if (a == 114)
		change_speed(win, 10);
	else if (a == 27)
		dead_end(inf);
	else if (a == 115)
		return (1);
	else if (a == 97)
		inf->win.speed = 0;
	return (0);
}

void		ncurses_trigger(t_info *inf, int iterations)
{
	t_win	*win;

	win = &(inf->win);
	if (win->speed)
		usleep(win->speed);
	while (1)
	{
		write_stats(inf, win, iterations);
		wrefresh(win->info);
		if (get_command(inf))
			break ;
		if (win->pause == 0)
			break ;
	}
	wrefresh(win->main);
}
