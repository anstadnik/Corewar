/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   things_to_bytecode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 19:09:00 by byermak           #+#    #+#             */
/*   Updated: 2018/07/04 17:27:04 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	to_buff(char *buff, unsigned char c)
{
	static size_t i;

	buff[i++] = (char)c; //TODO: here is the issue with bigzork.s
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
