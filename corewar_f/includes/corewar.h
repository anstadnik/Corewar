/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 13:51:01 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/16 18:35:47 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				4

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		11
# define MAX_PLAYERS			4
# define MEM_SIZE				4096
# define IDX_MOD				512
# define CHAMP_MAX_SIZE			682

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536// Hm, shouldn't we change this time to time?
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define ABS(x) ((x) < 0 ? -(x) : (x))

typedef	char		t_arg_type;

# define T_REG					1
# define T_IND					2
# define T_DIR					4
# define T_LAB					8

# define NAME_LEN				(128)
# define COMMENT_LEN			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

# define FILE_MAX_LENGTH		(NAME_LEN + COMMENT_LEN + 16 + CHAMP_MAX_SIZE)

# define OUTPUT_NONE 			0
# define OUTPUT_TEXT 			1
# define OUTPUT_BIN				2
# define OUTPUT_NCUR			3

# define MAX_FUNC	 			16

# define PLAYER_CODE 			(-1)

typedef enum		e_args
{
	FLAG_A,
	FLAG_D,
	FLAG_S,
	FLAG_V,
	FLAG_B,
	FLAG_N
}					t_args;

typedef union		u_magic
{
	unsigned char	arr[4];
	int				magic;
}					t_magic;

typedef struct		s_header
{
	unsigned int		prog_size;
	char				prog_name[NAME_LEN + 1];
	char				comment[COMMENT_LEN + 1];
	int					player_number;
}					t_header;

typedef struct		s_info
{
	t_list				*stack;
	t_header			head[MAX_PLAYERS];
	t_header			*last_dead;
	int					args[7];
	int					cycles_to_die;
	int					output_mode;
	int					players[MAX_PLAYERS];
	int					players_amount;
	unsigned char		map[MEM_SIZE];
}					t_info;

typedef struct		s_carriage
{
	int				reg[REG_NUMBER];
	void			(*func)();
	int				carry;
	int				pc;
	int				cycles_left;
	int				map_start;
	int				*players;
	int				players_amount;
	int				lives;
	int				number;
	int				cycles_without_live;
}					t_carriage;

typedef struct		s_op
{
	void			(*func)();
	int				cycles;
	int				codage[3];
	int				cod_oct;
	int				lab;
}					t_op;

int					get_int(unsigned char *map, int pc);
int					get_short(unsigned char *map, int pc);
int					get_reg(unsigned char *map, int pc);
int					get_dir(unsigned char *map, int pc, int len);
int					get_ind(unsigned char *map, int pc);

int					*get_args(unsigned char *map, int st, int *args,
						int label_s);
int					*get_codage(unsigned char code);

void				cor_add(unsigned char *map, t_carriage *carry,
						int *codage, int *args);
void				cor_sub(unsigned char *map, t_carriage *carry,
						int *codage, int *args);
void				cor_and(unsigned char *map, t_carriage *carry,
						int *codage, int *args);
void				cor_or(unsigned char *map, t_carriage *carry,
						int *codage, int *args);
void				cor_xor(unsigned char *map, t_carriage *carry,
						int *codage, int *args);
//
void				cor_zjmp(unsigned char *map, t_carriage *carry);
//
void				cor_fork(unsigned char *map, t_carriage *carry);
//
void				cor_lfork(unsigned char *map, t_carriage *carry);
void				cor_aff(unsigned char *map, t_carriage *carry,
						int *codage, int *args);
//
void				cor_live(unsigned char *map, t_carriage *carry);
//
void				cor_st(unsigned char *map, t_carriage *carry,
						int *codage, int *args);
void				cor_sti(unsigned char *map, t_carriage *carry,
						int *codage, int *args);
void				cor_ld(unsigned char *map, t_carriage *carry,
						int *codage, int *args);
void				cor_ldi(unsigned char *map, t_carriage *carry,
						int *codage, int *args);
void				cor_lld(unsigned char *map, t_carriage *carry,
						int *codage, int *args);
void				cor_lldi(unsigned char *map, t_carriage *carry,
						int *codage, int *args);

void				get_parameters(int ac, char **av, t_info *inf);

void				read_players(t_info *inf);

void				main_cycle(t_info *inf);
void				cycle_to_die_func(t_info *inf, int iterations);
int					get_max_lives(t_info *inf);

void				new_carriage(t_list **add_pointer, t_list *lst);
int					get_args_flag(int *args, int flag);
t_header			*get_player_info(t_header *arr, int player);

void				print_v_16(unsigned char *map, int start, int end);
void				swap_union_mgc(t_magic *mgc);

int					errmsg(char *str);
void				*ft_memcpy_cor(void *str1, size_t start, const void *str2,
						size_t n);

void				output_text(t_info *inf, int iterations);
void				introduce(t_info *inf);
void				winner(t_info *inf);

#endif
