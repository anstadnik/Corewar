/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:06:00 by byermak           #+#    #+#             */
/*   Updated: 2018/07/06 20:00:06 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	push_back(t_code *new)
{
	t_code	*tmp;

	if (!g_code)
	{
		g_code = new;
		g_code->index = 0;
		return ;
	}
	tmp = g_code;
	while (tmp->next)
		tmp = tmp->next;
	new->index = tmp->index + 1 + ((tmp->codage) ? 1 : 0) + tmp->arg1->length +
		((tmp->arg2) ? tmp->arg2->length : 0) +
		((tmp->arg3) ? tmp->arg3->length : 0);
	tmp->next = new;
}

static char	count_codage(t_code *new)
{
	char	codage;

	codage = 0;
	if (g_op_tab[new->opcode - 1].codage_flag)
		codage = (char)((new->arg1->arg_code << 6) |
			((new->arg2) ? new->arg2->arg_code : 0) << 4 |
			((new->arg3) ? new->arg3->arg_code : 0) << 2);
	return (codage);
}

static int	new_command(char **comm, t_label **label, t_code **new, char *str)
{
	int	command_num;

	if (!(command_num = check_command(*comm)))
		return (new_command_error(comm, label, ERR_INVALID_COMMAND));
	if (!(*new = (t_code *)malloc(sizeof(t_code))))
		return (new_command_error(comm, label, ERR_MALLOC));
	(*new)->command = *comm;
	(*new)->opcode = command_num;
	(*new)->label = *label;
	(*new)->next = NULL;
	g_x += ft_strlen(*comm);
	if ((command_num = parse_args(str, *new)) != 1)
	{
		del_command(new);
		return (command_num);
	}
	(*new)->codage = count_codage(*new);
	push_back(*new);
	return (1);
}

static void	parse_command(char **str, t_label **label, int fd)
{
	int		i;
	char	*command;
	t_code	*new;

	if ((skip_spaces(*str)) == -1)
	{
		ft_strdel(str);
		skip_empty(fd, str);
	}
	i = (int)g_x;
	while ((*str)[i] && (*str)[i] != ' ' && (*str)[i] != '\t'
		&& (*str)[i] != DIRECT_CHAR)
		++i;
	command = ft_strsub(*str, (unsigned int)g_x, (size_t)(i - (int)g_x));
	if ((i = new_command(&command, label, &new, *str)) != 1)
		put_err(str, fd, i);
}

void		parse_code(int fd)
{
	char	*str;
	t_label	*label;
	t_code	*tmp;
	int		ret;

	skip_empty(fd, &str);
	if (!str)
		error_asm(NO_CODE, 0, NULL, fd);
	label = NULL;
	while (str && *str)
	{
		if ((ret = parse_labels(&str, &label, fd)) != 1)
			error_asm(ret, 0, &str, fd);
		if (!str)
			break ;
		parse_command(&str, &label, fd);
		ft_strdel(&str);
		skip_empty(fd, &str);
		label = NULL;
	}
	tmp = NULL;
	ret = 0;
	if ((ret = check_labels(tmp, ret, &label)) != 1)
		error_asm(WRONG_LABEL, 0, NULL, fd);
}
