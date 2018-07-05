/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytecode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:27:00 by byermak           #+#    #+#             */
/*   Updated: 2018/07/05 13:20:15 by byermak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	get_prog_size(void)
{
	t_code	*tmp;
	int		size;

	tmp = g_code;
	size = 0;
	while (tmp)
	{
		size += 1 + ((tmp->codage) ? 1 : 0) + tmp->arg1->length;
		size += (tmp->arg2) ? tmp->arg2->length : 0;
		size += (tmp->arg3) ? tmp->arg3->length : 0;
		tmp = tmp->next;
	}
	return (size);
}

static void			arg_to_bytecode(char *buff, t_arg *arg)
{
	if (arg->length == 1)
		to_buff(buff, (unsigned char)arg->value);
	else if (arg->length == 2)
		short_to_bytecode(buff, (unsigned short)arg->value);
	else
		int_to_bytecode(buff, (unsigned int)arg->value);
}

static void			command_to_bytecode(char *buff, t_code *command)
{
	to_buff(buff, (unsigned char)command->opcode);
	if (command->codage)
		to_buff(buff, (unsigned char)command->codage);
	arg_to_bytecode(buff, command->arg1);
	if (command->arg2)
		arg_to_bytecode(buff, command->arg2);
	if (command->arg3)
		arg_to_bytecode(buff, command->arg3);
}

void				to_bytecode(t_header *magic, int fd)
{
	const int	len = get_prog_size() + PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	char		buff[len];
	t_code		*tmp;

	ft_bzero(buff, (size_t)len);
	magic->magic = COREWAR_EXEC_MAGIC;
	magic->prog_size = (unsigned int)get_prog_size();
	int_to_bytecode(buff, magic->magic);
	str_to_bytecode(buff, magic->prog_name, PROG_NAME_LENGTH);
	int_to_bytecode(buff, 0);
	int_to_bytecode(buff, magic->prog_size);
	str_to_bytecode(buff, magic->comment, COMMENT_LENGTH);
	int_to_bytecode(buff, 0);
	tmp = g_code;
	while (tmp)
	{
		command_to_bytecode(buff, tmp);
		tmp = tmp->next;
	}
	write(fd, &buff, (size_t)len);
	del_code();
}
