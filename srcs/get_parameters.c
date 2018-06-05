/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 18:11:13 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/04 19:37:31 by bcherkas         ###   ########.fr       */
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
	else if (ft_strequ(str, "-b"))
		return (FLAG_B);
	else if (ft_strequ(str, "-n"))
		return (FLAG_N);
	else if (ft_strequ(str, "-a"))
		return (FLAG_A);
	else
		return (-1);
}

void	get_player(char *str, t_info *inf)
{
	if (ft_strequ(str, "--stealth"))
		errmsg("Invalid parameter");
	inf->players++;
	if (inf->players > MAX_PLAYERS)
		errmsg("Too many players");
	inf->fd[inf->players - 1] = open(str, O_RDONLY);
	if (inf->fd[inf->players - 1] < 0)
		errmsg("No such file or you dont have enough rights");
}

void	get_output(char *str, int *ind, ssize_t *ret, int mode)
{
	if (mode == FLAG_D || mode == FLAG_S || mode == FLAG_V)
	{
		(*ind)++;
		if (!str || !ft_isinteger(str))
			errmsg("Invalid parameter");
		if (*ret > -1)
			errmsg("Duplicated parameters");
		*ret = ft_atoi(str);
		if (*ret < 0)
			errmsg("Invalid parameter");
	}
	else if (mode == FLAG_B || mode == FLAG_N || mode == FLAG_A)
	{
		if (*ret > -1)
			errmsg("Duplicated parameters");
		*ret = 1;
		if (ft_strequ(str, "--stealth") && mode != FLAG_A)
		{
			(*ind)++;
			(*ret)++;
		}
	}
}

void	excludes(ssize_t *args)
{
	int		text_out;
	int		bin_out;
	int		ncur_out;

	text_out = (args[FLAG_V] > -1 || args[FLAG_D] > -1 || args[FLAG_S] > -1) ? 1 : 0;
	bin_out = args[FLAG_B] > -1 ? 1 : 0;
	ncur_out = args[FLAG_N] > -1 ? 1 : 0;
	if ((text_out && bin_out) || (bin_out && ncur_out) ||
		(text_out && ncur_out))
		errmsg("You can have only one output mode");
}

void	get_parameters(int ac, char **av, t_info *inf)
{
	int		i;
	int		ret;

	i = 0;
	while (i < ac)
	{
		ret = check_parameter(av[i]);
		if (ret < 0)
			get_player(av[i], inf);
		else
			get_output(av[i + 1], &i, &(inf->args[ret]), ret);
		i++;
	}
	i = 0;
	while (i < 6)
	{
		printf("%ld\n", inf->args[i]);
		i++;
	}
	excludes(inf->args);
	if (inf->players < 1)
		errmsg("To few players");
}
