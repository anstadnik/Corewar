/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:30:00 by lburlach          #+#    #+#             */
/*   Updated: 2018/07/04 15:35:23 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include <fcntl.h>
# include <limits.h>

# define ERR_NO_CODE						(-1)//"No code in file" +
# define ERR_INVALID_COMMAND				(-2)//"Invalid command" +
# define ERR_NO_COMMAND_ARGS				(-3)//"No command arguments" +
# define ERR_MALLOC							(-4)//"Malloc error"
# define ERR_INVALID_ARG					(-5)//"Invalid chars in arg"
# define ERR_INVALID_T_REG					(-6)//"Invalid number of register(chars)"
# define ERR_INVALID_T_DIR					(-7)//"Invalid number in T_DIR"
# define ERR_INVALID_T_IND					(-8)//"Invalid number in T_IND"
# define ERR_INVALID_NUMBER_OF_REG			(-9)//"Invalid number(<1 || >REG_NUMBER)"
# define ERR_UNKNOWN_CHAR_AFTER_FIRST_ARG	(-10)
# define ERR_UNKNOWN_CHAR_AFTER_SECOND_ARG	(-11)
# define ERR_ENDLINE						(-12)//"Error in end of line(separator)"
# define ERR_INVALID_0_PAR_T_REG			(-13)//"Invalid parameter 0 type register for instruction live"
# define ERR_INVALID_0_PAR_T_DIR			(-14)
# define ERR_INVALID_0_PAR_T_IND			(-15)
# define ERR_INVALID_1_PAR_T_REG			(-16)
# define ERR_INVALID_1_PAR_T_DIR			(-17)
# define ERR_INVALID_1_PAR_T_IND			(-18)
# define ERR_INVALID_2_PAR_T_REG			(-19)
# define ERR_INVALID_2_PAR_T_DIR			(-20)
# define ERR_INVALID_2_PAR_T_IND			(-21)
# define ERR_INVALID_NUMBER_OF_ARGS			(-22)//"Too few args"
# define ERR_WRONG_LABEL					(-23) // +


typedef	struct	s_arg
{
	char			arg_type;// T_REG | T_DIR | T_IND
	char			arg_code;// REG_CODE | DIR_CODE | IND_CODE
	char			label_flag;
	char			*label;
	unsigned char	length;
	int				value;
}				t_arg;

typedef struct	s_code
{
	char			*command;
	int				opcode;
	char			codage;
	char			*label;
	t_arg			*arg1;
	t_arg			*arg2;
	t_arg			*arg3;
	unsigned char	index;
	struct s_code	*next;

}				t_code;

typedef struct	s_op
{
	char	*command;
	char	args_num;
	char	args[3];
	char	label_size;
	char	codage_flag;
}				t_op;

static const t_op	g_op_tab[16] = {
	{"live",	1, {T_DIR, 0, 0}, 4, 0},
	{"ld", 		2, {T_DIR | T_IND, T_REG, 0}, 4, 1},
	{"st",		2, {T_REG, T_IND | T_REG, 0}, 4, 1},
	{"add",		3, {T_REG, T_REG, T_REG}, 4, 1},
	{"sub",		3, {T_REG, T_REG, T_REG}, 4, 1},
	{"and",		3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 4, 1},
	{"or",		3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 4, 1},
	{"xor",		3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 4, 1},
	{"zjmp",	1, {T_DIR, 0, 0}, 2, 0},
	{"ldi",		3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 2, 1},
	{"sti",		3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 2, 1},
	{"fork",	1, {T_DIR, 0, 0}, 2, 0},
	{"lld",		2, {T_DIR | T_IND, T_REG, 0}, 4, 1},
	{"lldi",	3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 2, 1},
	{"lfork",	1, {T_DIR, 0, 0}, 2, 0},
	{"aff",		1, {T_REG, 0, 0}, 4, 1}};

size_t	g_count;
size_t	g_x;
t_code	*g_code;

enum	g_err {
	WRONG_INSTR = 1,
	READING_ERR,
	NAME_INC,
	WHIT_AF_TAB,
	UNSUF_INFO,
	LONG_CHAMP_NAME,
	WHIT_AF_TAB_C,
	END_LINE_BTW_INSTR,
	NO_CODE,
	WRONG_LABEL,
	WRONG_COM,
	MALLOC_ERR,
	NO_COM_ARGS,
	WRONG_SEP,
	INVAL_ARG,
	ERR_INV_T_REG,
	INV_NUM_REG,
	INV_T_DIR,
	INV_T_IND,
	UKN_CHAR_F_C,
	UKN_CHAR_S_C,
	NUM_OF_ARGS
};

void	parse_name_and_comment(int fd, t_header *magic_structure);
void	usage(void);
void	error_ac(char *s);
void	error_asm(int err_num, size_t x, char **code, int fd);
void	fetch_the_name(char **line, int fd, size_t row, t_list **head);
char	*retrieve_comment(int fd);
void	skip_whitespaces(int fd, char **line);
ssize_t	str_from_lsts(t_list *tmp, char **line);

void	parse_code(int fd);
void	del_command(t_code **new);
void	del_code(void);
void	to_bytecode(t_header *magic, int fd);
void	to_buff(char *buff, unsigned char c);
void	int_to_bytecode(char *buff, unsigned int num);
void	short_to_bytecode(char *buff, unsigned short int num);
void	str_to_bytecode(char *buff, char *str, int len);
int		label_error(void);
char	*parse_label(char *str);
int		check_labels(t_code *tmp, int label_index);
int		new_command_error(char **command, char **label, int error);
int		skip_spaces(char *str);
void	skip_empty(int fd, char **str);
int		word(char *str, int i);
int		parse_arg(char *str, t_arg **arg);
int		parse_args(char *str, t_code *new);
t_arg	*new_arg(char arg_code, char label_flag, int value, char *label);
int		check_first_arg(t_code *new);
int		check_second_arg(t_code *new);
int		check_third_arg(t_code *new);
int		check_command(char *command);


void	put_err(char **str, int fd, int i);

#endif
