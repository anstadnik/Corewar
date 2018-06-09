/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 13:51:01 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/09 11:59:23 by astadnik         ###   ########.fr       */
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

typedef	char		t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
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
	char			arr[4];
	unsigned		magic;
}					t_magic;

typedef struct		s_header
{
	unsigned int		prog_size;
	char				prog_name[NAME_LEN + 1];
	char				comment[COMMENT_LEN + 1];
}					t_header;

typedef struct		s_info
{
	t_list				*stack;
	t_header			head[MAX_PLAYERS];
	ssize_t				args[7];
	int					cycles_to_die;
	int					output_mode;
	// Changed, cause I'll use it also for counting lifes(weird, I know)
	// We can discuss it and revert if u mind
	int					players[MAX_PLAYERS];
	int					players_amount;
	int					carriage_number;
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
	int				players_amount;// I need to know it to not say life to smbd
	// who doesn't exist
	int				lives;// Make it 0 where this stuff is initialized
	// If it's 0 - no "live" for 1 CYCLE_TO_DIE
	// If it's -1 - ... for 2 CYCLE_TO_DIE (REMOVE!!!)
}					t_carriage;

typedef struct		s_op
{
	void			(*func)();
	int				code;
	int				cycles;
}					t_op;

void				get_parameters(int ac, char **av, t_info *inf);

void				read_players(t_info *inf);

void				main_cycle(t_info *inf, unsigned char *map);
void				new_carriage(t_list **add_pointer, t_list *lst);

int					get_int(unsigned char *map, int pc);
short int			get_short(unsigned char *map, int pc);
int					get_reg(unsigned char *map, int pc);
int					get_dir(unsigned char *map, int pc, int len);
int					get_ind(unsigned char *map, int pc);
void				get_args(unsigned char *map, int start, int *args,
		int *codage);

//

void				cor_add(unsigned char *map, t_carriage *carry);
void				cor_sub(unsigned char *map, t_carriage *carry);
void				cor_and(unsigned char *map, t_carriage *carry);
void				cor_or(unsigned char *map, t_carriage *carry);
void				cor_xor(unsigned char *map, t_carriage *carry);
//
void				cor_zjmp(unsigned char *map, t_carriage *carry);
//
void				cor_fork(unsigned char *map, t_carriage *carry);
//
void				cor_lfork(unsigned char *map, t_carriage *carry);
void				cor_aff(unsigned char *map, t_carriage *carry, ssize_t a);
//
void				cor_live(unsigned char *map, t_carriage *carry);

void				output_text(t_info *inf, int iterations);

int					errmsg(char *str);

void				printmap(unsigned char *map);
void				print_stack(t_list *tmp);

#endif
