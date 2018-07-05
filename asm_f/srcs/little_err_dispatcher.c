/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_err_dispatcher.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:55:00 by lburlach          #+#    #+#             */
/*   Updated: 2018/07/04 15:35:23 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	put_err(char **str, int fd, int i)
{
	if (i == ERR_MALLOC)
		error_asm(MALLOC_ERR, g_x, str, fd);
	else if (i == ERR_NO_COMMAND_ARGS)
		error_asm(NO_COM_ARGS, g_x, str, fd);
	else if (i == ERR_ENDLINE)
		error_asm(WRONG_SEP, g_x, str, fd);
	else if (i == ERR_INVALID_ARG)
		error_asm(INVAL_ARG, g_x, str ,fd);
	else if (i == ERR_INVALID_T_REG || i == ERR_INVALID_0_PAR_T_REG || i == ERR_INVALID_1_PAR_T_REG || i == ERR_INVALID_2_PAR_T_REG)
		error_asm(ERR_INV_T_REG, g_x, str ,fd);
	else if (i == ERR_INVALID_NUMBER_OF_REG)
		error_asm(INV_NUM_REG, g_x, str, fd);
	else if (i == ERR_INVALID_T_DIR || i == -14 || i == -17 || i == -20)
		error_asm(INV_T_DIR, g_x, str, fd);
	else if (i == ERR_INVALID_T_IND || i == -15 || i == -18 || i == -21)
		error_asm(INV_T_IND, g_x, str, fd);
	else if (i == ERR_UNKNOWN_CHAR_AFTER_FIRST_ARG)
		error_asm(UKN_CHAR_F_C, g_x, str, fd);
	else if (i == ERR_UNKNOWN_CHAR_AFTER_SECOND_ARG)
		error_asm(UKN_CHAR_S_C, g_x, str, fd);
	else if (i == ERR_INVALID_NUMBER_OF_ARGS)
		error_asm(NUM_OF_ARGS, g_x, str, fd);
	else
		error_asm(WRONG_COM, g_x, str, fd);
}
