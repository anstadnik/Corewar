/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytecode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:27:00 by byermak           #+#    #+#             */
/*   Updated: 2018/06/13 18:53:43 by byermak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static unsigned int	get_prog_size(void)
{
	t_code			*tmp;
	unsigned int	size;

	tmp = g_code;
	while (tmp->next)
		tmp = tmp->next;
	size = tmp->index + 1 + ((tmp->codage) ? 1 : 0) + tmp->arg1->length;
	size += (tmp->arg2) ? tmp->arg2->length : 0;
	size += (tmp->arg3) ? tmp->arg3->length : 0;
	return (size);
}

static void			to_buff(char *buff, char c)
{
	static size_t i;

	buff[i++] = c;
}

void				int_to_bytecode(char *buff, unsigned int num)
{
	to_buff(buff, (num >> 24));
	to_buff(buff, (num << 8) >> 24);
	to_buff(buff, (num << 16) >> 24);
	to_buff(buff, (num << 24) >> 24);
}

void				short_to_bytecode(char *buff, unsigned short int num)
{
	to_buff(buff, (num >> 8));
	to_buff(buff, (num << 8) >> 8);
}

void				str_to_bytecode(char *buff, char *str, int len)
{
	int	i;

	i = 0;
	while (str[i])
		to_buff(buff, str[i++]);
	while (i++ < len)
		to_buff(buff, 0);
}

void				arg_to_bytecode(char *buff, t_arg *arg)
{
	if (arg->length == 1)
		to_buff(buff, (unsigned char)arg->value);
	else if (arg->length == 2)
		short_to_bytecode(buff, (unsigned short)arg->value);
	else
		int_to_bytecode(buff, (unsigned int)arg->value);
}

void				command_to_bytecode(char *buff, t_code *command)
{
	to_buff(buff, (char)command->opcode);
	if (command->codage)
		to_buff(buff, command->codage);
	arg_to_bytecode(buff, command->arg1);
	if (command->arg2)
		arg_to_bytecode(buff, command->arg2);
	if (command->arg3)
		arg_to_bytecode(buff, command->arg3);
}

void				to_bytecode(t_header *magic, int fd)
{
	const int	len = get_prog_size() + PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	char		str[len];
	t_code		*tmp;

	ft_bzero(str, (size_t)len);
	magic->magic = COREWAR_EXEC_MAGIC;
	magic->prog_size = get_prog_size();
	int_to_bytecode(str, magic->magic);
	str_to_bytecode(str, magic->prog_name, PROG_NAME_LENGTH);
	int_to_bytecode(str, 0);
	int_to_bytecode(str, magic->prog_size);
	str_to_bytecode(str, magic->comment, COMMENT_LENGTH);
	int_to_bytecode(str, 0);
	tmp = g_code;
	while (tmp)
	{
		command_to_bytecode(str, tmp);
		tmp = tmp->next;
	}
	write(fd, &str, len);
}
