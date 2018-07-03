/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:14:00 by byermak           #+#    #+#             */
/*   Updated: 2018/06/16 14:14:22 by byermak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	del_command(t_code **new)
{
	if ((*new)->label)
		ft_strdel(&(*new)->label);
	ft_strdel(&(*new)->command);
	if ((*new)->arg1)
	{
		if ((*new)->arg1->label)
			ft_strdel(&(*new)->arg1->label);
		free((*new)->arg1);
	}
	if ((*new)->arg2)
	{
		if ((*new)->arg2->label)
			ft_strdel(&(*new)->arg2->label);
		free((*new)->arg2);
	}
	if ((*new)->arg3)
	{
		if ((*new)->arg1->label)
			ft_strdel(&(*new)->arg3->label);
		free((*new)->arg3);
	}
	free(*new);
	*new = NULL;
}

void	del_code(void)
{
	t_code	*tmp;

	while (g_code)
	{
		tmp = g_code->next;
		del_command(&g_code);
		g_code = tmp;
	}
}
