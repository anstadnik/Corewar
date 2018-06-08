/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 18:51:41 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/08 15:37:01 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "corewar.h"

void	cor_aff(unsigned char *map, t_carriage *carry);

/*
 ** op_tab: 
 ** 1. function pointer,           2. number of args,
 ** 3. code of function,          4. can change carry or no,
 ** 5. have codage octet or no,   6.number of cycles it need,
 ** 7. size of label
 */
/*
t_op    op_tab[MAX_FUNCTIONS] =
{
	{cor_live, 1, 0x01, 0, 0, 10, 4},
	{cor_ld, 2, 0x02, 1, 0, 5, 4},
	{cor_st, 2, 0x03, 0, 1, 5, 4},
	{cor_add, 1, 0x04, 1, 1, 10, 4},
	{cor_sub, 1, 0x05, 1, 1, 10, 4},
	{cor_and, 1, 0x06, 1, 1, 6, 4},
	{cor_or, 1, 0x07, 1, 1, 6, 4},
	{cor_xor, 1, 0x08, 1, 1, 6, 4},
	{cor_zjmp, 1, 0x09, 0, 0, 20, 2},
	{cor_ldi, 1, 0x0a, 0, 1, 25, 2},
	{cor_sti, 1, 0x0b, 0, 1, 25, 2},
	{cor_fork, 1, 0x0c, 0, 0, 800, 2},
	{cor_lld, 1, 0x0d, 1, 1, 10, 4},
	{cor_lldi, 1, 0x0e, 1, 1, 50, 2},
	{cor_lfork, 1, 0x0f, 0, 0, 1000, 2},
	{cor_aff, 1, 0x10, 0, 1, 2, 4}
};
*/

t_op    op_tab[MAX_FUNC] =
{
	{NULL, 1, 0x01, 0, 0, -1, 0},
	{NULL, 1, 0x02, 0, 0, -1, 0},
	{NULL, 1, 0x03, 0, 0, -1, 0},
	{NULL, 1, 0x04, 0, 0, -1, 0},
	{NULL, 1, 0x05, 0, 0, -1, 0},
	{NULL, 1, 0x06, 0, 0, -1, 0},
	{NULL, 1, 0x07, 0, 0, -1, 0},
	{NULL, 1, 0x08, 0, 0, -1, 0},
	{cor_zjmp, 1, 0x09, 0, 0, 20, 2},
	{NULL, 1, 0x0a, 0, 0, -1, 0},
	{NULL, 1, 0x0b, 0, 0, -1, 0},
	{cor_fork, 1, 0x0c, 0, 0, 800, 2},
	{NULL, 1, 0x0d, 0, 0, -1, 0},
	{NULL, 1, 0x0e, 0, 0, -1, 0},
	{cor_lfork, 1, 0x0f, 0, 0, 1000, 2},
	{cor_aff, 1, 0x10, 0, 1, 2, 4}
};

void	wrapper(unsigned char *map, t_carriage *carry, ssize_t *args)
{
	int		func_num;

	func_num = map[carry->pc];
	if (carry->cycles_left > 1)
		carry->cycles_left--;
	else if (carry->cycles_left == 0 && func_num <= MAX_FUNC && func_num > 0)
	{
		carry->func = op_tab[func_num - 1].func;
		carry->cycles_left = op_tab[func_num - 1].cycles + 1;
	}
	else if (carry->cycles_left == 0 && (func_num > MAX_FUNC || func_num < 1))
		carry->pc = (carry->pc + 1) % MEM_SIZE;
	else if (carry->cycles_left == 1 && func_num < MAX_FUNC)
	{
		carry->func(map, carry);
		carry->cycles_left--;
	}
	else if (carry->cycles_left == 1 && func_num == MAX_FUNC)
	{
		if (args[FLAG_A] > 0)
			cor_aff(map, carry);
		carry->pc = (carry->pc + 3) % MEM_SIZE;
		carry->cycles_left--;
	}
}

int		check_lives(t_info *inf)
{
	t_list		*ptr;
	t_carriage	*carriage;
	int			i;
	int			alives;

	ptr = inf->stack;
	while (ptr)
	{
		carriage = ptr->content;
		if (carriage->lives > 0)
			carriage->lives = 0; // OK
		else if (!carriage->lives)
			carriage->lives = -1; // No live for 1 cycle_to_die, hm
		else if (carriage->lives == -1)
			ft_lstdelnode(&inf->stack, ptr); // No live for 2 cycle_to_die, EXTERMINATUS
		// TODO What happens if there r no carriages?
	}
	i = inf->players_amount;
	alives = 0;
	while (i--)
	{
		inf->players[i] = inf->players[i] > 0 ? 0 : -1; // If 0 or -1 we make it -1
		//which means he's dead
		//which we gotta check in live function
		alives += inf->players[i] == 0;
	}
	return (alives == 0);
}

void	main_cycle(t_info *inf, unsigned char *map)
{
	t_list	*lst;
	int		iterations;

	iterations = 0;
	ft_bzero(inf->players, sizeof(inf->players));
	while (42)
	{
		lst = inf->stack;
		while (lst)
		{
			wrapper(map, (t_carriage *)lst->content, inf->args);
			lst = lst->next;
		}
		iterations++;
		if (iterations + 1 % CYCLE_TO_DIE == 0)
			if (check_lives(inf))
				return ;
			// return to prev function to make -b output and print result
		// Output function
		if (inf->output_mode == 1)
			output_text(inf, iterations);
	}
}
