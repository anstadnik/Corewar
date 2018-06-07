/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:30:00 by lburlach          #+#    #+#             */
/*   Updated: 2018/06/07 18:15:38 by byermak          ###   ########.fr       */
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

#define ERR_NO_CODE -1 //"No code in file"
#define ERR_INVALID_COMMAND -2 //"Invalid command"
#define ERR_NO_COMMAND_ARGS -3 //"No command arguments"
#define ERR_MALLOC -4 //"Malloc error"
#define ERR_FIRST_ARG -5 //"something with first argument"
#define ERR_SECOND_ARG -6 //"something with second argument"
#define ERR_THIRD_ARG -7 //"something with third argument"

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

typedef	struct	s_arg
{
	char arg; // T_REG_CODE | T_DIR_CODE | T_IND_CODE
	char label_flag; // 1 | 0
	char *value;
}				t_arg;

typedef struct	s_code
{
	char			*command; //or a number?
	int				comand_num;
	char			*label;
	t_arg			*arg1;
	t_arg			*arg2;
	t_arg			*arg3;
	size_t			index; //order number
	struct s_code	*next;

}				t_code;

size_t	g_count;
size_t	g_x;
t_code	*g_code;

void	parse_name_and_comment(int fd, header_t *magic_structure);
void	parse_code(int fd/*, t_code **code*/);
void	usage(void);
void	error_ac(char *s);
void	error_asm(char *err, size_t y, size_t x, char *code);

#endif
