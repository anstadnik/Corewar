/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 13:51:01 by bcherkas          #+#    #+#             */
/*   Updated: 2018/07/06 21:30:10 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <ncurses.h>

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				4

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		11
# define MAX_PLAYERS			4
# define MEM_SIZE				4096
# define MAX_NUMBER				5376
# define IDX_MOD				512
# define CHAMP_MAX_SIZE			682

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define ABS(x) ((x) < 0 ? -(x) : (x))

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

typedef struct		s_win
{
	WINDOW			*main;
	WINDOW			*info;
	int				pause;
	int				iter_per_sec;
	unsigned		speed;
}					t_win;

typedef struct		s_header
{
	unsigned int		prog_size;
	int					player_number;
	char				prog_name[NAME_LEN + 1];
	char				comment[COMMENT_LEN + 1];
}					t_header;

typedef struct		s_info
{
	t_header			head[MAX_PLAYERS];
	t_win				win;
	t_list				*stack;
	t_header			*last_dead;
	int					args[7];
	int					cycles_to_die;
	int					output_mode;
	int					players[MAX_PLAYERS];
	int					players_amount;
	int					carriages;
	unsigned char		map[MEM_SIZE];
}					t_info;

typedef struct		s_carriage
{
	void			(*func)();
	int				reg[REG_NUMBER];
	int				carry;
	int				pc;
	int				cycles_left;
	int				map_start;
	int				*players;
	int				players_amount;
	int				lives;
	int				number;
	int				cycles_without_live;
	int				player_num;
	int				func_num;
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
int					*get_codage(unsigned char code, const int *func_code);

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
void				cor_zjmp(unsigned char *map, t_carriage *carry);
void				cor_fork(unsigned char *map, t_carriage *carry);
void				cor_lfork(unsigned char *map, t_carriage *carry);
void				cor_aff(unsigned char *map, t_carriage *carry,
						int *codage, int *args);
void				cor_live(unsigned char *map, t_carriage *carry);
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
void				cycle_to_die_func(t_info *inf);

void				new_carriage(t_info *inf, t_list *lst);
int					get_args_flag(int *args, int flag);
t_header			*get_player_info(t_header *arr, int player);

void				print_v_16(unsigned char *map, int start, int end);
void				swap_union_mgc(t_magic *mgc);

int					errmsg(char *str);
void				*ft_memcpy_cor(void *str1, size_t start, const void *str2,
						size_t n);

//void				lst_foreach(t_info *inf, void (*f)(t_list *, t_info *));
//void				del_node(t_list *lst, t_info *inf);

void				ncur_init_window(t_info *inf);
void				color_output(int player, unsigned char *str, int start,
						size_t len);
WINDOW				*get_active_window(int num, WINDOW *main, WINDOW *info);
void				stop_ncurses(t_info *inf);

void				ncurses_trigger(t_info *inf, int iterations);
void				ncur_print_carry(t_carriage *carry, int symbol, int mode);

int					alldead(t_info *inf);
void				output_text(t_info *inf, int iterations);
void				introduce(t_info *inf);
void				winner(t_info *inf);
void				dead_end(t_info *inf);

#endif
