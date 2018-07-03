/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 15:19:00 by byermak           #+#    #+#             */
/*   Updated: 2018/06/16 15:19:00 by byermak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	check_command(char *command)
{
	int	i;

	i = 0;
	while (i < 16)
		if (ft_strequ(command, g_op_tab[i++].command))
			return (i);
	return (0);
}



int	check_third_arg(t_code *new)
{
	int		i;

	i = new->opcode - 1;
	if (!new->arg3 && g_op_tab[i].args_num > 2)
		return (ERR_INVALID_NUMBER_OF_ARGS);
	if ((new->arg3->arg_type & g_op_tab[i].args[2]) != new->arg3->arg_type)
	{
		if (new->arg3->arg_type == T_REG)
			return (ERR_INVALID_2_PAR_T_REG);
		else if (new->arg3->arg_type == T_DIR)
			return (ERR_INVALID_2_PAR_T_DIR);
		return (ERR_INVALID_2_PAR_T_IND);
	}
	if (new->arg3->arg_type == T_DIR)
		new->arg3->length = (unsigned char)g_op_tab[i].label_size;
	if (new->arg3->arg_type == T_DIR && new->arg3->length == 2)
		if (new->arg3->value > USHRT_MAX)
			return (ERR_INVALID_T_DIR);
	return (1);
}

int	check_second_arg(t_code *new)
{
	int		i;

	i = new->opcode - 1;
	if (!new->arg2 && g_op_tab[i].args_num > 1)
		return (ERR_INVALID_NUMBER_OF_ARGS);
	if ((new->arg2->arg_type & g_op_tab[i].args[1]) != new->arg2->arg_type)
	{
		if (new->arg2->arg_type == T_REG)
			return (ERR_INVALID_1_PAR_T_REG);
		else if (new->arg2->arg_type == T_DIR)
			return (ERR_INVALID_1_PAR_T_DIR);
		return (ERR_INVALID_1_PAR_T_IND);
	}
	if (new->arg2->arg_type == T_DIR)
		new->arg2->length = (unsigned char)g_op_tab[i].label_size;
	if (new->arg2->arg_type == T_DIR && new->arg2->length == 2)
		if (new->arg2->value > USHRT_MAX)
			return (ERR_INVALID_T_DIR);
	return (1);
}

int	check_first_arg(t_code *new)
{
	int		i;

	i = new->opcode - 1;
	if ((new->arg1->arg_type & g_op_tab[i].args[0]) != new->arg1->arg_type)
	{
		if (new->arg1->arg_type == T_REG)
			return (ERR_INVALID_0_PAR_T_REG);
		else if (new->arg1->arg_type == T_DIR)
			return (ERR_INVALID_0_PAR_T_DIR);
		return (ERR_INVALID_0_PAR_T_IND);
	}
	if (new->arg1->arg_type == T_DIR)
		new->arg1->length = (unsigned char)g_op_tab[i].label_size;
	if (new->arg1->arg_type == T_DIR && new->arg1->length == 2)
		if (new->arg1->value > USHRT_MAX)
			return (ERR_INVALID_T_DIR);
	return (1);
}
