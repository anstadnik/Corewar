/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:28:00 by byermak           #+#    #+#             */
/*   Updated: 2018/07/04 13:26:20 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	new_command_error(char **command, t_label **label, int error)
{
	ft_strdel(command);
	del_labels(label);
	return (error);
}

int	label_error(void)
{
	return (-1);
}
