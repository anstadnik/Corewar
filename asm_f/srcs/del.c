/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:14:00 by byermak           #+#    #+#             */
/*   Updated: 2018/07/05 16:58:38 by byermak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	del_command(t_code **new)
{
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
	del_labels(&(*new)->label);
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

void	del_labels(t_label **label)
{
	t_label	*tmp;

	while (*label)
	{
		tmp = (*label)->next;
		if ((*label)->label)
			ft_strdel(&(*label)->label);
		free(*label);
		*label = tmp;
	}
}
