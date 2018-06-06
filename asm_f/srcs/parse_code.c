/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:06:00 by byermak           #+#    #+#             */
/*   Updated: 2018/06/06 20:25:40 by byermak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		skip_empty(int fd, char **str)
{
	int	ret;

	ret = get_next_line(fd, str);
	while ((ft_strlen(*str) == 0 || **str == '#') && ret == 1)
	{
		ft_strdel(str);
		ret = get_next_line(fd, str);
		++g_count;
	}
//	if (ret == 0)
//		*str = 0;
}

static char	*parse_label(char *str)
{

}

void		parse_code(int fd, t_command **code)
{
	char	*str;
	char	*label;

	skip_empty(fd, &str);
//	if (!str)
//		error(ERR_NO_CODE);
	while (*str)
	{
		label = parse_label(str);
		////parser
		ft_strdel(&str);
		skip_empty(fd, &str);
	}
	ft_strdel(&str);
}
