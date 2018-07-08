/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   things_to_bytecode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 19:09:00 by byermak           #+#    #+#             */
/*   Updated: 2018/07/02 16:30:07 by byermak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	to_buff(char *buff, unsigned char c)
{
	buff[g_i] = (char)c;
	++g_i;
}

void	int_to_bytecode(char *buff, unsigned int num)
{
	to_buff(buff, (num >> 24));
	to_buff(buff, (num << 8) >> 24);
	to_buff(buff, (num << 16) >> 24);
	to_buff(buff, (num << 24) >> 24);
}

void	short_to_bytecode(char *buff, unsigned short int num)
{
	to_buff(buff, (unsigned char)(num >> 8));
	to_buff(buff, (unsigned char)((num << 8) >> 8));
}

void	str_to_bytecode(char *buff, char *str, int len)
{
	int	i;

	i = 0;
	while (str[i])
		to_buff(buff, (unsigned char)str[i++]);
	while (i++ < len)
		to_buff(buff, 0);
}
