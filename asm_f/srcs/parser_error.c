/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:28:00 by byermak           #+#    #+#             */
/*   Updated: 2018/06/16 15:36:27 by byermak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	new_command_error(char **command, char **label, int error)
{
	ft_strdel(command);
	ft_strdel(label);
	return (error);
}

int	label_error(char *label)
{
	ft_printf("\n\n[Invalid label: %s]\n", label);
	exit(1);/////
	////Wrong label error
	return (ERR_WRONG_LABEL);
}
