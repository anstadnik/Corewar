/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:30:00 by lburlach          #+#    #+#             */
/*   Updated: 2018/07/06 19:59:42 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include <fcntl.h>
# include <limits.h>

# define ERR_INVALID_COMMAND				(-2)
# define ERR_NO_COMMAND_ARGS				(-3)
# define ERR_MALLOC							(-4)
# define ERR_INVALID_ARG					(-5)
# define ERR_INVALID_T_REG					(-6)
# define ERR_INVALID_T_DIR					(-7)
# define ERR_INVALID_T_IND					(-8)
# define ERR_INVALID_NUMBER_OF_REG			(-9)
# define ERR_UNKNOWN_CHAR_AFTER_FIRST_ARG	(-10)
# define ERR_UNKNOWN_CHAR_AFTER_SECOND_ARG	(-11)
# define ERR_ENDLINE						(-12)
# define ERR_INVALID_0_PAR_T_REG			(-13)
# define ERR_INVALID_0_PAR_T_DIR			(-14)
# define ERR_INVALID_0_PAR_T_IND			(-15)
# define ERR_INVALID_1_PAR_T_REG			(-16)
# define ERR_INVALID_1_PAR_T_DIR			(-17)
# define ERR_INVALID_1_PAR_T_IND			(-18)
# define ERR_INVALID_2_PAR_T_REG			(-19)
# define ERR_INVALID_2_PAR_T_DIR			(-20)
# define ERR_INVALID_2_PAR_T_IND			(-21)
# define ERR_INVALID_NUMBER_OF_ARGS			(-22)

typedef struct		s_label
{
	char			*label;
	struct s_label	*next;
}					t_label;

typedef	struct		s_arg
{
	char			arg_type;
	char			arg_code;
	char			label_flag;
	char			*label;
	unsigned char	length;
	unsigned int	value;
}					t_arg;

typedef struct		s_code
{
	char			*command;
	int				opcode;
	char			codage;
	t_label			*label;
	t_arg			*arg1;
	t_arg			*arg2;
	t_arg			*arg3;
	int				index;
	struct s_code	*next;

}					t_code;

typedef struct		s_op
{
	char	*command;
	char	args_num;
	char	args[3];
	char	label_size;
	char	codage_flag;
}					t_op;

static const t_op	g_op_tab[16] = {
	{"live", 1, {T_DIR, 0, 0}, 4, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG, 0}, 4, 1},
	{"st", 2, {T_REG, T_IND | T_REG, 0}, 4, 1},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 1},
	{"sub", 3, {T_REG, T_REG, T_REG}, 4, 1},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 4, 1},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 4, 1},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 4, 1},
	{"zjmp", 1, {T_DIR, 0, 0}, 2, 0},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 2, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 2, 1},
	{"fork", 1, {T_DIR, 0, 0}, 2, 0},
	{"lld", 2, {T_DIR | T_IND, T_REG, 0}, 4, 1},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 2, 1},
	{"lfork", 1, {T_DIR, 0, 0}, 2, 0},
	{"aff", 1, {T_REG, 0, 0}, 4, 1}};

size_t				g_count;
size_t				g_x;
t_code				*g_code;
size_t				g_i;

enum				e_err {
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

void				parse_name_and_comment(int fd, t_header *magic_structure);
void				usage(void);
void				error_asm(int err_num, size_t x, char **code, int fd);
void				fetch_the_name(char **line, int fd, size_t row,
								t_list **head);
char				*retrieve_comment(int fd);
void				skip_whitespaces(int fd, char **line);
ssize_t				str_from_lsts(t_list *tmp, char **line);
void				parse_code(int fd);
void				del_command(t_code **new);
void				del_code(void);
void				del_labels(t_label **label);
void				to_bytecode(t_header *magic, char **filename);
void				to_buff(char *buff, unsigned char c);
void				int_to_bytecode(char *buff, unsigned int num);
void				short_to_bytecode(char *buff, unsigned short int num);
void				str_to_bytecode(char *buff, char *str, int len);
int					label_error(void);
int					parse_label(char *str, t_label **label);
int					check_labels(t_code *tmp, int label_index, t_label **last);
int					new_command_error(char **command, t_label **label,
										int error);
int					skip_spaces(char *str);
void				skip_empty(int fd, char **str);
int					word(char *str, int i);
int					parse_arg(char *str, t_arg **arg);
int					parse_args(char *str, t_code *new);
t_arg				*new_arg(char arg_code, char label_flag, int value,
							char *label);
int					check_first_arg(t_code *new);
int					check_second_arg(t_code *new);
int					check_third_arg(t_code *new);
int					check_command(char *command);
int					get_prog_size(void);
void				put_err(char **str, int fd, int i);
long long			ft_atol(const char *s);
int					parse_labels(char **str, t_label **label, int fd);
int					push_back_label(t_label **label, char *label_str);

#endif
