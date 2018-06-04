/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 13:51:01 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/04 19:22:48 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

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

# include "libft.h"

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
	int				magic;
}					t_magic;

typedef struct		s_header
{
	char				prog_name[NAME_LEN + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LEN + 1];
}					t_header;

typedef struct		s_info
{
	ssize_t				args[6];
	struct s_header		head[MAX_PLAYERS];
	int					fd[MAX_PLAYERS];
	unsigned char		map[MEM_SIZE];
	t_list				*start;
	t_list				*end;
}					t_info;

typedef struct		s_carriage
{
	unsigned		reg[REG_NUMBER];
	int				carry;
	int				pc;
	void			(*func)(struct s_carriage *carriage, unsigned *map);
	int				cycles_to_start;
}					t_carriage;

int					check_file(int fd, t_header *head);

int					errmsg(char *str);

#endif
