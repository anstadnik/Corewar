/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 15:13:00 by byermak           #+#    #+#             */
/*   Updated: 2018/06/16 15:13:23 by byermak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static unsigned long	count(int n)
{
	unsigned long	rez;

	rez = n <= 0 ? 1 : 0;
	while (n)
	{
		rez++;
		n /= 10;
	}
	return (rez);
}

static int				parse_t_reg(char **str, t_arg **arg)
{
	int	value;
	int i;

	value = ft_atoi(*str + 1);
	i = 1;
	while ((*str)[i])
		if (!ft_isdigit((*str)[i++]))
		{
			ft_strdel(str);
			return (ERR_INVALID_T_REG);
		}
	ft_strdel(str);
	if (value < 1 || value > REG_NUMBER)
		return (ERR_INVALID_NUMBER_OF_REG);
	if (!(*arg = new_arg(REG_CODE, 0, value, NULL)))
		return (ERR_MALLOC);
	(*arg)->length = 1;
	return (1);
}

static int				parse_t_dir(char **str, t_arg **arg)
{
	int		value;
	char	label_flag;
	char	*label;

	label = NULL;
	value = ft_atoi(*str + 1);
	label_flag = (*(*str + 1) == LABEL_CHAR) ? (char)1 : (char)0;
	if (!label_flag && count(value) < ft_strlen(*str + 1))
	{
		ft_strdel(str);
		return (ERR_INVALID_T_DIR);
	}
	if (!label_flag)
		ft_strdel(str);
	else
		label = ft_strdup(*str + 2);
	ft_strdel(str);
	if (!(*arg = new_arg(DIR_CODE, label_flag, value, label)))
		return (ERR_MALLOC);
	return (1);
}

static int				parse_t_ind(char **str, t_arg **arg)
{
	int		value;
	char	label_flag;
	char	*label;

	value = ft_atoi(*str);
	label = NULL;
	label_flag = (**str == LABEL_CHAR) ? (char)1 : (char)0;
	if ((!label_flag && count(value) < ft_strlen(*str)) || value > USHRT_MAX)
	{
		ft_strdel(str);
		return (ERR_INVALID_T_IND);
	}
	if (!label_flag)
		ft_strdel(str);
	else
		label = ft_strdup(*str + 1);
	ft_strdel(str);
	if (!(*arg = new_arg(IND_CODE, label_flag, value, label)))
		return (ERR_MALLOC);
	(*arg)->length = 2;
	return (1);
}

int					parse_arg(char *str, t_arg **arg)
{
	if (*str == 'r')
		return (parse_t_reg(&str, arg));
	else if (*str == DIRECT_CHAR)
		return (parse_t_dir(&str, arg));
	else if (ft_isdigit(*str) || *str == LABEL_CHAR)
		return (parse_t_ind(&str, arg));
	else
	{
		ft_strdel(&str);
		return (ERR_INVALID_ARG);
	}
}
