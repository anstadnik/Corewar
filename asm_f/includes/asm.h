/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:30:00 by lburlach          #+#    #+#             */
/*   Updated: 2018/06/06 20:16:08 by byermak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include <fcntl.h>

# define T_REG_CODE 1
# define T_DIR_CODE 2
# define T_IND_CODE 3

#define ERR_NO_CODE "No code in file"

static const char	*g_comands[] = {
	"live",
	"ld",
	"st",
	"add",
	"sub",
	"and",
	"or",
	"xor",
	"zjmp",
	"ldi",
	"sti",
	"fork",
	"lld",
	"lldi",
	"lfork",
	"aff"};

size_t g_count;

typedef	struct	s_arg
{
	char arg; // T_REG_CODE | T_DIR_CODE | T_IND_CODE
	char label_flag; // 1 | 0
	char *value;
}				t_arg;

typedef struct	s_command
{
	char	*command; //or a number?
	char	comand_num;
	char	*label;
	t_arg	*arg1;
	t_arg	*arg2;
	t_arg	*arg3;
	size_t	index; //order number

}				t_command;

void	parse_name_and_comment(int fd, header_t *magic_structure);
void	parse_code(int fd, t_command **code);
void	usage(void);
void	error_ac(char *s);
void	error_asm(char *err, size_t y, size_t x, char *code);

#endif
