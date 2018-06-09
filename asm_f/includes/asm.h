/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:30:00 by lburlach          #+#    #+#             */
/*   Updated: 2018/06/09 18:59:33 by byermak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include <fcntl.h>
# include <limits.h>

# define ERR_NO_CODE -1					//"No code in file"
# define ERR_INVALID_COMMAND -2			//"Invalid command"
# define ERR_NO_COMMAND_ARGS -3			//"No command arguments"
# define ERR_MALLOC -4					//"Malloc error"
# define ERR_INVALID_ARG -5				//"Invalid chars in arg"
# define ERR_INVALID_T_REG -6			//"Invalid number of register(chars)"
# define ERR_INVALID_T_DIR -7			//"Invalid number in T_DIR"
# define ERR_INVALID_T_IND -8			//"Invalid number in T_IND"
# define ERR_INVALID_NUMBER_OF_REG -9	//"Invalid number(<1 || >REG_NUMBER)"
# define ERR_UNKNOWN_CHAR_AFTER_FIRST_ARG -10
# define ERR_UNKNOWN_CHAR_AFTER_SECOND_ARG -11
# define ERR_ENDLINE -12				//"Error in end of line(separator)"



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
	char	arg_type; // REG_CODE | DIR_CODE | IND_CODE
	char	label_flag; // 1 | 0
	char	*label;
	int		value;
}				t_arg;

typedef struct	s_code
{
	char			*command; //or a number?
	int				comand_num;
	size_t 			line;
	char			codage;
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
