/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 15:15:00 by byermak           #+#    #+#             */
/*   Updated: 2018/07/02 16:21:09 by byermak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_arg		*new_arg(char arg_code, char label_flag, int value, char *label)
{
	t_arg	*new;

	if (!(new = (t_arg *)malloc(sizeof(t_arg))))
		return (NULL);
	new->arg_code = arg_code;
	if (arg_code == REG_CODE)
		new->arg_type = T_REG;
	else if (arg_code == DIR_CODE)
		new->arg_type = T_DIR;
	else
		new->arg_type = T_IND;
	new->label_flag = label_flag;
	new->value = value;
	new->label = label;
	return (new);
}

static int	parse_third_arg(char *str, t_arg **arg)
{
	int i;
	int ret;

	if (str[g_x] != SEPARATOR_CHAR)
		return (ERR_UNKNOWN_CHAR_AFTER_SECOND_ARG);
	++g_x;
	if ((i = skip_spaces(str)) == -1)
		return (ERR_ENDLINE);
	i = word(str, i);
	if ((ret = (parse_arg(ft_strsub(str,
			(unsigned int)g_x, (size_t)(i - (int)g_x)), arg))) != 1)
		return (ret);
	g_x = (size_t)i;
	return (1);
}

static int	parse_second_arg(char *str, t_arg **arg)
{
	int i;
	int ret;

	if (str[g_x] != SEPARATOR_CHAR)
		return (ERR_UNKNOWN_CHAR_AFTER_FIRST_ARG);
	++g_x;
	if ((i = skip_spaces(str)) == -1)
		return (ERR_ENDLINE);
	i = word(str, i);
	if ((ret = (parse_arg(ft_strsub(str,
			(unsigned int)g_x, (size_t)(i - (int)g_x)), arg))) != 1)
		return (ret);
	g_x = (size_t)i;
	return (1);
}

int			parse_args(char *str, t_code *new)
{
	int		i;
	int		ret;

	new->arg1 = NULL;
	new->arg2 = NULL;
	new->arg3 = NULL;
	if ((i = skip_spaces(str)) == -1)
		return (ERR_NO_COMMAND_ARGS);
	i = word(str, i);
	if ((ret = (parse_arg(ft_strsub(str, (unsigned int)g_x, (size_t)(i - (int)
			g_x)), &(new->arg1)))) != 1 || (ret = check_first_arg(new)) != 1)
		return (ret);
	if ((g_x = (size_t)i) && (skip_spaces(str)) != -1)
	{
		if ((ret = parse_second_arg(str, &(new->arg2))) != 1 ||
			(ret = check_second_arg(new)) != 1)
			return (ret);
		if ((skip_spaces(str)) != -1)
			if ((ret = parse_third_arg(str, &(new->arg3))) != 1 ||
				(ret = check_third_arg(new)) != 1)
				return (ret);
		if ((skip_spaces(str)) != -1)
			return (ERR_ENDLINE);
	}
	return (1);
}
