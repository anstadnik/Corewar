/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:58:07 by lburlach          #+#    #+#             */
/*   Updated: 2018/07/06 19:54:10 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

ssize_t		str_from_lsts(t_list *tmp, char **line)
{
	t_list			*beg;
	ssize_t			i;
	ssize_t			c;

	c = 0;
	beg = tmp;
	while (beg)
	{
		c += beg->content_size;
		beg = beg->next;
	}
	(*line) = ft_memalloc((size_t)c + 1);
	if (*line == NULL)
		return (-1);
	i = 0;
	while (tmp)
	{
		ft_memcpy(&(*line)[i], tmp->content, tmp->content_size);
		i += (tmp->content_size);
		tmp = tmp->next;
	}
	return (c);
}

long long	ft_atol(const char *s)
{
	char		neg;
	long long	rez;

	rez = 0;
	neg = 0;
	while (ft_iswhitespace(*s))
		s++;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			neg = 1;
	while (*s == '0')
		s++;
	while (ft_isdigit(*s))
	{
		rez = rez * 10 + (unsigned long long)(*s++ - '0');
	}
	return (neg ? -1 * (long long)rez : (long long)rez);
}

void		put_err(char **str, int fd, int i)
{
	if (i == ERR_MALLOC)
		error_asm(MALLOC_ERR, g_x, str, fd);
	else if (i == ERR_NO_COMMAND_ARGS)
		error_asm(NO_COM_ARGS, g_x, str, fd);
	else if (i == ERR_ENDLINE)
		error_asm(WRONG_SEP, g_x, str, fd);
	else if (i == ERR_INVALID_ARG)
		error_asm(INVAL_ARG, g_x, str, fd);
	else if (i == ERR_INVALID_T_REG || i == ERR_INVALID_0_PAR_T_REG ||
			i == ERR_INVALID_1_PAR_T_REG || i == ERR_INVALID_2_PAR_T_REG)
		error_asm(ERR_INV_T_REG, g_x, str, fd);
	else if (i == ERR_INVALID_NUMBER_OF_REG)
		error_asm(INV_NUM_REG, g_x, str, fd);
	else if (i == ERR_INVALID_T_DIR || i == -14 || i == -17 || i == -20)
		error_asm(INV_T_DIR, g_x, str, fd);
	else if (i == ERR_INVALID_T_IND || i == -15 || i == -18 || i == -21)
		error_asm(INV_T_IND, g_x, str, fd);
	else if (i == ERR_UNKNOWN_CHAR_AFTER_FIRST_ARG)
		error_asm(UKN_CHAR_F_C, g_x, str, fd);
	else if (i == ERR_UNKNOWN_CHAR_AFTER_SECOND_ARG)
		error_asm(UKN_CHAR_S_C, g_x, str, fd);
	else if (i == ERR_INVALID_NUMBER_OF_ARGS)
		error_asm(NUM_OF_ARGS, g_x, str, fd);
	else
		error_asm(WRONG_COM, g_x, str, fd);
}
