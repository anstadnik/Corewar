/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parameters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 18:11:13 by bcherkas          #+#    #+#             */
/*   Updated: 2018/07/08 17:17:29 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_parameter(char *str)
{
	if (ft_strequ(str, "-d"))
		return (FLAG_D);
	else if (ft_strequ(str, "-s"))
		return (FLAG_S);
	else if (ft_strequ(str, "-v"))
		return (FLAG_V);
	else if (ft_strequ(str, "--ncurses"))
		return (FLAG_N);
	else if (ft_strequ(str, "-a"))
		return (FLAG_A);
	else if (ft_strequ(str, "-A"))
		return (FLAG_A);
	else if (ft_strequ(str, "-n"))
		return (FLAG_P);
	else if (ft_strequ(str, "--dump"))
		return (FLAG_DUMP);
	else
		return (-1);
}

void	get_player(char *str, t_info *inf, int *number)
{
	if (inf->players_amount >= MAX_PLAYERS)
		errmsg("Too many players");
	inf->players[inf->players_amount] = open(str, O_RDONLY);
	if (number[inf->players_amount] == -1)
		number[inf->players_amount] = inf->players_amount + 1;
	if (inf->players[inf->players_amount] < 0)
		errmsg("No such file or you dont have enough rights");
	inf->players_amount++;
}

void	get_output(char *str, int *ind, int *ret, int mode)
{
	if (mode == FLAG_D || mode == FLAG_S || mode == FLAG_V || mode == FLAG_DUMP)
	{
		(*ind)++;
		if (!str || ft_isinteger(str))
			errmsg("Invalid parameter");
		if (*ret > -1)
			errmsg("Duplicated parameters");
		*ret = ft_atoi(str);
		*ret = *ret < 0 ? -1 : *ret;
	}
	else if (mode == FLAG_N || mode == FLAG_A)
	{
		if (*ret > -1)
			errmsg("Duplicated parameters");
		*ret = 1;
	}
}

void	get_player_number(t_info *inf, int *i, char **av, int *numbers)
{
	int		ret;

	(*i)++;
	if (!av[*i] || ft_isinteger(av[*i]))
		errmsg("Invalid parameter");
	numbers[inf->players_amount] = ft_atoi(av[*i]);
	(*i)++;
	if (!av[*i])
		errmsg("Invalid parameter");
	if ((ret = check_parameter(av[*i]) == -1))
		get_player(av[*i], inf, numbers);
	else if (ret == FLAG_P)
		errmsg("Several -n in a row");
	else
		errmsg("Flag -n \"number\" must be before bot name");
}

void	get_parameters(int ac, char **av, t_info *inf)
{
	int		i;
	int		ret;
	int		numbers[4];

	i = 0;
	SET_ARR(numbers, -1);
	while (i < ac)
	{
		ret = check_parameter(av[i]);
		if (ret < 0)
			get_player(av[i], inf, numbers);
		else if (ret == FLAG_P)
			get_player_number(inf, &i, av, numbers);
		else if (ret == FLAG_A && ft_strequ(av[i], "-A"))
			inf->args[FLAG_A] = 2;
		else
			get_output(av[i + 1], &i, &(inf->args[ret]), ret);
		i++;
	}
	if (inf->args[FLAG_N] > -1 && (inf->args[FLAG_V] > -1
			|| inf->args[FLAG_D] > -1 || inf->args[FLAG_S] > -1))
		errmsg("You can have only one output mode");
	inf->args[FLAG_S] = inf->args[FLAG_S] == 0 ? -1 : inf->args[FLAG_S];
	sort_linked_arrs(inf->players, numbers, 4);
}
