/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:06:00 by byermak           #+#    #+#             */
/*   Updated: 2018/06/07 19:15:48 by byermak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	skip_spaces(char *str)
{
	while (str[g_x] && (str[g_x] == ' ' || str[g_x] == '\t'))
		++g_x;
	if (!str[g_x])
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

static int	parse_arg(char *str, t_arg **arg)
{
//	int		i;
//	char	*value;
//
//	////продумать чтобы перед первым и после последнего аргумента не было ,
//	*arg = NULL;
//	i = skip_spaces(str);
//	if (str[i] == SEPARATOR_CHAR && ++g_x)
//		i = skip_spaces(str);
//	if (i != -1)
//	{
//		if (str[i] == SEPARATOR_CHAR)
//
//		while (str[i] && str[i] != ' ' && str[i] != '\t')
//			++i;
//		value = ft_strsub(str, g_x, i - g_x);
//		////parse
//	}
//	return (0);
}

static int	parse_args(char	*str, t_code *new)
{
	int		i;
	int		ret;

	new->arg2 = NULL;
	new->arg3 = NULL;
	if ((i = skip_spaces(str)) == -1)
		return (ERR_NO_COMMAND_ARGS);
	while (str[i] && str[i] != ' ' && str[i] != '\t')
		++i;
	if ((parse_arg(ft_strsub(str, g_x, i - g_x), &(new->arg1))) != 1)
		return (ERR_FIRST_ARG);
	if ((i = skip_spaces(str)) > 0)
	{
		////// parse second and third args
	}
	return (1);
}

static int	new_command(char **comm, char **label, t_code **new, char **str)
{
	int	command_num;

	if (!(command_num = check_command(*comm)))
		return (new_command_error(comm, label, ERR_INVALID_COMMAND));
	if (!(*new = (t_code *)malloc(sizeof(t_code))))
		return (new_command_error(comm, label, ERR_MALLOC));
	(*new)->command = *comm;
	(*new)->comand_num = command_num;
	(*new)->label = *label;
	(*new)->next = NULL;
	g_x += ft_strlen(*comm);
	if ((command_num = parse_args(*comm, *new)) != 1)
	{
		free(new);
		new_command_error(comm, label, command_num);
	}
//	parse_arg(*str, &((*new)->arg1));
//	parse_arg(*str, &((*new)->arg2));
//	parse_arg(*str, &((*new)->arg3));
////	check endline
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
	if ((i = new_command(&command, label, &new, str)) != 1)
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
