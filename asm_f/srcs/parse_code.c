/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:06:00 by byermak           #+#    #+#             */
/*   Updated: 2018/06/16 15:34:29 by byermak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

//static void				print_args(t_code *new)
//{
//	ft_printf("t:[%i] f:[%i] l:[%s] v:[%i] length:[%i]\n", new->arg1->arg_type, new->arg1->label_flag, new->arg1->label, new->arg1->value, new->arg1->length);
//	if (new->arg2)
//		ft_printf("t:[%i] f:[%i] l:[%s] v:[%i] length:[%i]\n", new->arg2->arg_type, new->arg2->label_flag, new->arg2->label, new->arg2->value, new->arg2->length);
//	if (new->arg3)
//		ft_printf("t:[%i] f:[%i] l:[%s] v:[%i] length:[%i]\n", new->arg3->arg_type, new->arg3->label_flag, new->arg3->label, new->arg3->value, new->arg3->length);
//	ft_printf("////////////////////////////////////\n\n");
//}
//
//static void				print_comands()
//{
//	t_code	*tmp;
//
//	tmp = g_code;
//	while (tmp)
//	{
//		ft_printf("____________________________________\n");
//		ft_printf("name: %s[%i]\n", tmp->command, tmp->opcode);
//		ft_printf("index: %i\n", tmp->index);
//		ft_printf("label: %s\n", tmp->label);
//		ft_printf("codage: %x\n\n", tmp->codage);
//		print_args(tmp);
//		tmp = tmp->next;
//	}
//}

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
		codage = (new->arg1->arg_type << 6) |
			((new->arg2) ? new->arg2->arg_code : 0) << 4 |
			((new->arg3) ? new->arg3->arg_code : 0) << 2;
	return (codage);
}

static int	new_command(char **comm, char **label, t_code **new, char *str)
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

static void	parse_command(char **str, char **label, int fd)
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
	while ((*str)[i] && (*str)[i] != ' ' && (*str)[i] != '\t')
		++i;
	command = ft_strsub(*str, (int)g_x, i - g_x);
	if ((i = new_command(&command, label, &new, *str)) != 1)
	{
		ft_strdel(str);
		ft_printf("[%i]\n", i);
		exit(1);////////
////	free code and close fd
////	error(i);
	}
}

void		parse_code(int fd)
{
	char	*str;
	char	*label;
	t_code	*tmp;
	int		ret;

	skip_empty(fd, &str);
//	if (!str)
//		error(ERR_NO_CODE);
	while (str && *str)
	{
		label = parse_label(str);
		parse_command(&str, &label, fd);
		ft_strdel(&str);
		skip_empty(fd, &str);
	}
	if ((ret = check_labels(tmp, ret)) != 1)
		;//error(ret)
}
