/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 13:51:01 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/06 20:54:51 by bcherkas         ###   ########.fr       */
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

# define CYCLE_TO_DIE			1536
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

# define PLAYER_CODE 			0xffffff

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
	int					fd[MAX_PLAYERS];
	int					players;
	int					carriage_number;
	unsigned char		map[MEM_SIZE];
}					t_info;

typedef struct		s_carriage
{
	unsigned		reg[REG_NUMBER];
	void			(*func)();
	int				carry;
	int				pc;
	int				cycles_start;
	int				map_start;
}					t_carriage;

typedef struct		s_op
{
	void			(*func)();
	int				args_num;
	int				code;
	int				carry;
	int				codage;
	int				cycles;
	int				label_size;
}					t_op;

void				get_parameters(int ac, char **av, t_info *inf);

void				read_players(t_info *inf);

void				main_cycle(t_info *inf, unsigned char *map);

int					errmsg(char *str);

void				printmap(unsigned char *map);
void				print_stack(t_list *tmp);

#endif
