/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_other.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 15:10:00 by byermak           #+#    #+#             */
/*   Updated: 2018/06/16 15:10:02 by byermak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				skip_spaces(char *str)
{
	while (str[g_x] && (str[g_x] == ' ' || str[g_x] == '\t'))
		++g_x;
	if (!str[g_x] || str[g_x] == COMMENT_CHAR)
		return (-1);
	return (int)g_x;
}

void			skip_empty(int fd, char **str)
{
	int	ret;

	g_x = 0;
	ret = get_next_line(fd, str);
	++g_count;
	while (ret == 1 && (ft_strlen(*str) == 0 || **str == COMMENT_CHAR ||
						(skip_spaces(*str) == -1)))
	{
		g_x = 0;
		ft_strdel(str);
		ret = get_next_line(fd, str);
		++g_count;
	}
}

int				word(char *str, int i)
{
	while (str[i] && str[i] != ' ' && str[i] != '\t' &&
		   str[i] != SEPARATOR_CHAR)
		++i;
	return (i);
}
