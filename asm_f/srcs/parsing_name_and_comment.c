/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_name_and_comment.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:44:00 by lburlach          #+#    #+#             */
/*   Updated: 2018/06/06 16:09:37 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	parse_name_and_comment(int fd, header_t *magic_structure)
{
	char *line;
	int i;

	i = 0;
	while (get_next_line(fd, &line) && i < 2)
	{
		ft_printf("%s\n", line);
		ft_strdel(&line);
		i++;
	}
}
