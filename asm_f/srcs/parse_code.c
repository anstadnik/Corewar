/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:06:00 by byermak           #+#    #+#             */
/*   Updated: 2018/06/09 19:18:45 by byermak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
	return g_x;
}

static void	skip_empty(int fd, char **str)
{
	int	ret;

	g_x = 0;
	ret = get_next_line(fd, str);
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
	label = check_label(ft_strsub(str, g_x, tmp - (str + g_x)));
	g_x += ft_strlen(label) + 1;
	return (label);
}

static int	new_command_error(char **command, char **label, int error)
{
	ft_strdel(command);
	ft_strdel(label);
	return (error);
}

static char	check_command(char *command)
{
	char	i;

	while (i < 16)
		if (ft_strequ(command, g_comands[i++]))
			return (i);
	return (0);
}

static t_arg	*new_arg(char arg_type, char label_flag, int value, char *label)
{
	t_arg	*new;

	if (!(new = (t_arg *)malloc(sizeof(t_arg))))
		return (NULL);
	new->arg_type = arg_type;
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
	return (1);
}

static int	parse_t_dir(char **str, t_arg **arg)
{
	int		value;
	char	label_flag;

	value = ft_atoi(*str + 1);
	label_flag = (*(*str + 1) == LABEL_CHAR) ? 1 : 0;
	if (!label_flag && count(value) < ft_strlen(*str + 1))
	{
		ft_strdel(str);
		return (ERR_INVALID_T_DIR);
	}
	if (!label_flag)
		ft_strdel(str);
	else
		ft_strncpy(*str, *str + 2, ft_strlen(*str));
	if (!(*arg = new_arg(DIR_CODE, label_flag, value, *str)))
		return (ERR_MALLOC);
	return (1);
}

static int	parse_t_ind(char **str, t_arg **arg)
{
	int		value;
	char	label_flag;

	value = ft_atoi(*str);
	label_flag = (*(*str) == LABEL_CHAR) ? 1 : 0;
	if ((!label_flag && count(value) < ft_strlen(*str)) || value > USHRT_MAX)
	{
		ft_strdel(str);
		return (ERR_INVALID_T_IND);
	}
	if (!label_flag)
		ft_strdel(str);
	else
		ft_strncpy(*str, *str + 1, ft_strlen(*str));
	if (!(*arg = new_arg(IND_CODE, label_flag, value, *str)))
		return (ERR_MALLOC);
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
	g_x = i;
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
	g_x = i;
	return (1);
}

static int	parse_args(char	*str, t_code *new)
{
	int		i;
	int		ret;

	new->arg2 = NULL;
	new->arg3 = NULL;
	if ((i = skip_spaces(str)) == -1)
		return (ERR_NO_COMMAND_ARGS);
	i = word(str, i);
	if ((ret = (parse_arg(ft_strsub(str, g_x, i - g_x), &(new->arg1)))) != 1)
		return (ret);
	g_x = i;
	if ((skip_spaces(str)) != -1)
	{
		if ((ret = parse_second_arg(str, &(new->arg2))) != 1)
			return (ret);
		if ((skip_spaces(str)) != -1)
		{
			if ((ret = parse_third_arg(str, &(new->arg3))) != 1)
				return (ret);
		}
		if ((skip_spaces(str)) != -1)
			return (ERR_ENDLINE);
	}
	return (1);
}

static void	print_args(t_code *new)
{
	ft_printf("____________________________________\n");
	ft_printf("t:[%i] f:[%i] l:[%s] v:[%i]\n", new->arg1->arg_type, new->arg1->label_flag, new->arg1->label, new->arg1->value);
	if (new->arg2)
		ft_printf("t:[%i] f:[%i] l:[%s] v:[%i]\n", new->arg2->arg_type, new->arg2->label_flag, new->arg2->label, new->arg2->value);
	if (new->arg3)
		ft_printf("t:[%i] f:[%i] l:[%s] v:[%i]\n", new->arg3->arg_type, new->arg3->label_flag, new->arg3->label, new->arg3->value);

	ft_printf("////////////////////////////////////\n\n");
}

static int	new_command(char **comm, char **label, t_code **new, char *str)
{
	int	command_num;

	if (!(command_num = check_command(*comm)))
		return (new_command_error(comm, label, ERR_INVALID_COMMAND));
	if (!(*new = (t_code *)malloc(sizeof(t_code))))
		return (new_command_error(comm, label, ERR_MALLOC));
	(*new)->command = *comm;
	(*new)->line = g_count;
	(*new)->comand_num = command_num;
	(*new)->label = *label;
	(*new)->next = NULL;
	g_x += ft_strlen(*comm);
	if ((command_num = parse_args(str, *new)) != 1)
	{
		free(new);
		new_command_error(comm, label, command_num);
	}
	print_args(*new);

////	check args
////	push_back_new_command(new);
	return (1);
}

static void	parse_command(char **str/*, t_code **code*/, char **label, int fd)
{
	int			i;
	char		*command;
	t_code	*new;

	if ((skip_spaces(*str)) == -1)
	{
		ft_strdel(str);
		skip_empty(fd, str);
	}
	i = g_x;
	while ((*str)[i] && (*str)[i] != ' ' && (*str)[i] != '\t')
		++i;
	command = ft_strsub(*str, g_x, i - g_x);
	if ((i = new_command(&command, label, &new, *str)) != 1)
	{
		ft_strdel(str);
////	free code and close fd
////	error(i);
	}
//	parse_command_args(str, new);
//	g_x += i - g_x;
//	if ((skip_spaces(*str)) == -1)
//	{
//		ft_strdel(str);
//		ft_strdel(command);
//		error(ERR_NO_COMMAND_ARGS);
//	}
//	ft_printf("[%s]  [%s]\n", command, *str + g_x);
}

void		parse_code(int fd/*, t_code **code*/)
{
	char	*str;
	char	*label;

	skip_empty(fd, &str);
//	if (!str)
//		error(ERR_NO_CODE);
	while (str && *str)
	{
		label = parse_label(str);
		parse_command(&str, /*code, */&label, fd);
//		ft_printf("{%i}[%s] -> %s\n", g_x, str + g_x, label);
		////parser
		ft_strdel(&str);
//		ft_strdel(&label);
		skip_empty(fd, &str);
	}
}
