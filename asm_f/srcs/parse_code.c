/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:06:00 by byermak           #+#    #+#             */
/*   Updated: 2018/06/13 14:07:34 by byermak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	print_args(t_code *new)
{
	ft_printf("t:[%i] f:[%i] l:[%s] v:[%i] length:[%i]\n", new->arg1->arg_type, new->arg1->label_flag, new->arg1->label, new->arg1->value, new->arg1->length);
	if (new->arg2)
		ft_printf("t:[%i] f:[%i] l:[%s] v:[%i] length:[%i]\n", new->arg2->arg_type, new->arg2->label_flag, new->arg2->label, new->arg2->value, new->arg2->length);
	if (new->arg3)
		ft_printf("t:[%i] f:[%i] l:[%s] v:[%i] length:[%i]\n", new->arg3->arg_type, new->arg3->label_flag, new->arg3->label, new->arg3->value, new->arg3->length);
	ft_printf("////////////////////////////////////\n\n");
}

static void	print_comands()
{
	t_code	*tmp;

	tmp = g_code;
	while (tmp)
	{
		ft_printf("____________________________________\n");
		ft_printf("name: %s[%i]\n", tmp->command, tmp->opcode);
		ft_printf("index: %i\n", tmp->index);
		ft_printf("label: %s\n", tmp->label);
		ft_printf("codage: %x\n\n", tmp->codage);
		print_args(tmp);
		tmp = tmp->next;
	}
}

static unsigned long	count(int n)
{
	unsigned long	rez;

	rez = n <= 0 ? 1 : 0;
	while (n)
	{
		rez++;
		n /= 10;
	}
	return (rez);
}

static int	skip_spaces(char *str)
{
	while (str[g_x] && (str[g_x] == ' ' || str[g_x] == '\t'))
		++g_x;
	if (!str[g_x] || str[g_x] == COMMENT_CHAR)
		return (-1);
	return (int)g_x;
}

static void	skip_empty(int fd, char **str)
{
	int	ret;

	g_x = 0;
	ret = get_next_line(fd, str);
	++g_count;
	while (ret == 1 && (ft_strlen(*str) == 0 || **str == COMMENT_CHAR ||
		(skip_spaces(*str) == -1)))
	{
		g_x = 0;
		ft_strdel(str);
		ret = get_next_line(fd, str);
		++g_count;
	}
}

static int	check_label_words(char c)
{
	int		i;
	char	*label_chars;

	i = 0;
	label_chars = LABEL_CHARS;
	while (label_chars[i])
		if (c == label_chars[i++])
			return (1);
	return (0);
}

static char	*check_label(char *label)
{
	t_code	*tmp;

	tmp = g_code;
	while (tmp)
	{
		if (ft_strequ(tmp->label, label))
		{
			ft_strdel(&label);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (label);
}

static char	*parse_label(char *str)
{
	char	*tmp;
	char	*label;
	size_t	i;

	i = g_x;
	tmp = ft_strchr(str, LABEL_CHAR);
	if (!tmp)
		return (NULL);
	while ((str + i) != tmp)
		if (!check_label_words(str[i++]))
			return (NULL);
	label = check_label(ft_strsub(str, (int)g_x, tmp - (str + g_x)));
	g_x += ft_strlen(label) + 1;
	return (label);
}

static int	new_command_error(char **command, char **label, int error)
{
	ft_strdel(command);
	ft_strdel(label);
	return (error);
}

static int	check_command(char *command)
{
	int	i;

	i = 0;
	while (i < 16)
		if (ft_strequ(command, g_op_tab[i++].command))
			return (i);
	return (0);
}

static t_arg	*new_arg(char arg_code, char label_flag, int value, char *label)
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

static int	parse_t_reg(char **str, t_arg **arg)
{
	int	value;
	int i;

	value = ft_atoi(*str + 1);
	i = 1;
	while ((*str)[i])
		if (!ft_isdigit((*str)[i++]))
		{
			ft_strdel(str);
			return (ERR_INVALID_T_REG);
		}
	ft_strdel(str);
	if (value < 1 || value > REG_NUMBER)
		return (ERR_INVALID_NUMBER_OF_REG);
	if (!(*arg = new_arg(REG_CODE, 0, value, NULL)))
		return (ERR_MALLOC);
	(*arg)->length = 1;
	return (1);
}

static int	parse_t_dir(char **str, t_arg **arg)
{
	int		value;
	char	label_flag;
	char	*label;

	label = NULL;
	value = ft_atoi(*str + 1);
	label_flag = (*(*str + 1) == LABEL_CHAR) ? (char)1 : (char)0;
	if (!label_flag && count(value) < ft_strlen(*str + 1))
	{
		ft_strdel(str);
		return (ERR_INVALID_T_DIR);
	}
	if (!label_flag)
		ft_strdel(str);
	else
		label = ft_strdup(*str + 2);
	ft_strdel(str);
	if (!(*arg = new_arg(DIR_CODE, label_flag, value, label)))
		return (ERR_MALLOC);
	return (1);
}

static int	parse_t_ind(char **str, t_arg **arg)
{
	int		value;
	char	label_flag;
	char	*label;

	value = ft_atoi(*str);
	label = NULL;
	label_flag = (**str == LABEL_CHAR) ? (char)1 : (char)0;
	if ((!label_flag && count(value) < ft_strlen(*str)) || value > USHRT_MAX)
	{
		ft_strdel(str);
		return (ERR_INVALID_T_IND);
	}
	if (!label_flag)
		ft_strdel(str);
	else
		label = ft_strdup(*str + 1);
	ft_strdel(str);
	if (!(*arg = new_arg(IND_CODE, label_flag, value, label)))
		return (ERR_MALLOC);
	(*arg)->length = 2;
	return (1);
}

static int	parse_arg(char *str, t_arg **arg)
{
	if (*str == 'r')
		return (parse_t_reg(&str, arg));
	else if (*str == DIRECT_CHAR)
		return (parse_t_dir(&str, arg));
	else if (ft_isdigit(*str) || *str == LABEL_CHAR)
		return (parse_t_ind(&str, arg));
	else
	{
		ft_strdel(&str);
		return (ERR_INVALID_ARG);
	}
}

static int	word(char *str, int i)
{
	while (str[i] && str[i] != ' ' && str[i] != '\t' &&
		str[i] != SEPARATOR_CHAR)
		++i;
	return (i);
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
	if ((ret = (parse_arg(ft_strsub(str, g_x, i - g_x), arg))) != 1)
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
	if ((ret = (parse_arg(ft_strsub(str, g_x, i - g_x), arg))) != 1)
		return (ret);
	g_x = (size_t)i;
	return (1);
}

static int	check_third_arg(t_code *new)
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
		new->arg3->length = g_op_tab[i].label_size;
	if (new->arg3->arg_type == T_DIR && new->arg3->length == 2)
		if (new->arg3->value > USHRT_MAX)
			return (ERR_INVALID_T_DIR);
	return (1);
}

static int	check_second_arg(t_code *new)
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
		new->arg2->length = g_op_tab[i].label_size;
	if (new->arg2->arg_type == T_DIR && new->arg2->length == 2)
		if (new->arg2->value > USHRT_MAX)
			return (ERR_INVALID_T_DIR);
	return (1);
}

static int	check_first_arg(t_code *new)
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
		new->arg1->length = g_op_tab[i].label_size;
	if (new->arg1->arg_type == T_DIR && new->arg1->length == 2)
		if (new->arg1->value > USHRT_MAX)
			return (ERR_INVALID_T_DIR);
	return (1);
}

static int	parse_args(char *str, t_code *new)
{
	int		i;
	int		ret;

	new->arg1 = NULL;
	new->arg2 = NULL;
	new->arg3 = NULL;
	if ((i = skip_spaces(str)) == -1)
		return (ERR_NO_COMMAND_ARGS);
	i = word(str, i);
	if ((ret = (parse_arg(ft_strsub(str, g_x, i - g_x), &(new->arg1)))) != 1 ||
		(ret = check_first_arg(new)) != 1)
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

static void	del_command(t_code **new)
{
	if ((*new)->label)
		ft_strdel(&(*new)->label);
	ft_strdel(&(*new)->command);
	if ((*new)->arg1)
	{
		if ((*new)->arg1->label)
			ft_strdel(&(*new)->arg1->label);
		free((*new)->arg1);
	}
	if ((*new)->arg2)
	{
		if ((*new)->arg2->label)
			ft_strdel(&(*new)->arg2->label);
		free((*new)->arg2);
	}
	if ((*new)->arg3)
	{
		if ((*new)->arg1->label)
			ft_strdel(&(*new)->arg3->label);
		free((*new)->arg3);
	}
	free(*new);
	*new = NULL;
}

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
////	free code and close fd
////	error(i);
	}
}

static int	label_error(char *label)
{
	////Wrong label error
	return (ERR_WRONG_LABEL);
}

static int	find_label(char *label)
{
	t_code	*tmp;

	tmp = g_code;
	while (tmp)
	{
		if (ft_strequ(label, tmp->label))
			return (tmp->index);
		tmp = tmp->next;
	}
	return (-1);
}

static int	check_labels(t_code *tmp, int label_index)
{
	tmp = g_code;
	while (tmp)
	{
		if (tmp->arg1->label_flag)
		{
			if ((label_index = find_label(tmp->arg1->label)) == -1)
				return (label_error(tmp->arg1->label));
			tmp->arg1->value = (unsigned char)label_index - tmp->index;
		}
		if (tmp->arg2 && tmp->arg2->label_flag)
		{
			if ((label_index = find_label(tmp->arg2->label)) == -1)
				return (label_error(tmp->arg2->label));
			tmp->arg2->value = (unsigned char)label_index - tmp->index;
		}
		if (tmp->arg3 && tmp->arg3->label_flag)
		{
			if ((label_index = find_label(tmp->arg3->label)) == -1)
				return (label_error(tmp->arg3->label));
			tmp->arg3->value = (unsigned char)label_index - tmp->index;
		}
		tmp = tmp->next;
	}
	return (1);
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
//		ft_printf("[%i]: %s\n", g_count + 1, str);
		ft_strdel(&str);
		skip_empty(fd, &str);
	}
	if ((ret = check_labels(tmp, ret)) != 1)
		;//error(ret)
//	print_comands();
}
