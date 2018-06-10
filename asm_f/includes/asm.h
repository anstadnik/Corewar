/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:30:00 by lburlach          #+#    #+#             */
/*   Updated: 2018/06/10 18:01:37 by byermak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include <fcntl.h>
# include <limits.h>

# define ERR_NO_CODE (-1)					//"No code in file"
# define ERR_INVALID_COMMAND (-2)			//"Invalid command"
# define ERR_NO_COMMAND_ARGS (-3)			//"No command arguments"
# define ERR_MALLOC (-4)					//"Malloc error"
# define ERR_INVALID_ARG (-5)				//"Invalid chars in arg"
# define ERR_INVALID_T_REG (-6)				//"Invalid number of register(chars)"
# define ERR_INVALID_T_DIR (-7)				//"Invalid number in T_DIR"
# define ERR_INVALID_T_IND (-8)				//"Invalid number in T_IND"
# define ERR_INVALID_NUMBER_OF_REG (-9)		//"Invalid number(<1 || >REG_NUMBER)"
# define ERR_UNKNOWN_CHAR_AFTER_FIRST_ARG (-10)
# define ERR_UNKNOWN_CHAR_AFTER_SECOND_ARG (-11)
# define ERR_ENDLINE (-12)					//"Error in end of line(separator)"

# define ERR_INVALID_0_PAR_T_REG (-13)
# define ERR_INVALID_0_PAR_T_DIR (-14)
# define ERR_INVALID_0_PAR_T_IND (-15)
# define ERR_INVALID_1_PAR_T_REG (-16)
# define ERR_INVALID_1_PAR_T_DIR (-17)
# define ERR_INVALID_1_PAR_T_IND (-18)
# define ERR_INVALID_2_PAR_T_REG (-19)
# define ERR_INVALID_2_PAR_T_DIR (-20)
# define ERR_INVALID_2_PAR_T_IND (-21)


typedef	struct	s_arg
{
	char	arg_type;// T_REG | T_DIR | T_IND
	char	arg_code;// REG_CODE | DIR_CODE | IND_CODE
	char	label_flag; // 1 | 0
	char	*label;
	int		value;
}				t_arg;

typedef struct	s_code
{
	char			*command; //or a number?
	int				comand_num;

	char			codage;
	char			*label;
	t_arg			*arg1;
	t_arg			*arg2;
	t_arg			*arg3;
	size_t			index; //order number
	struct s_code	*next;

}				t_code;

typedef struct	s_op
{
	char	*command;
	char	args_num;
	char	args[3];
	char	label_size;
}				t_op;

static const t_op	g_op_tab[16] = {
	{"live",	1, {T_DIR, 0, 0, 4}},
	{"ld", 		2, {T_DIR | T_IND, T_REG, 0}, 4},
	{"st",		2, {T_REG, T_IND | T_REG, 0}, 4},
	{"add",		3, {T_REG, T_REG, T_REG}, 4},
	{"sub",		3, {T_REG, T_REG, T_REG}, 4},
	{"and",		3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 4},
	{"or",		3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 4},
	{"xor",		3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 4},
	{"zjmp",	1, {T_DIR, 0, 0}, 2},
	{"ldi",		3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 2},
	{"sti",		3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 2},
	{"fork",	1, {T_DIR, 0, 0, 2}},
	{"lld",		2, {T_DIR | T_IND, T_REG, 0}, 4},
	{"lldi",	3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 2},
	{"lfork",	1, {T_DIR, 0, 0}, 2},
	{"aff",		1, {T_REG, 0, 0}, 4}};

size_t	g_count;
size_t	g_x;
t_code	*g_code;

void	parse_name_and_comment(int fd, header_t *magic_structure);
void	parse_code(int fd);
void	usage(void);
void	error_ac(char *s);
void	error_asm(char *err, size_t y, size_t x, char *code);

#endif
