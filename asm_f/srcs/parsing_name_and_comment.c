/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_name_and_comment.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:44:00 by lburlach          #+#    #+#             */
/*   Updated: 2018/07/08 20:49:14 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static size_t g_row;

static void	detect_the_beginning(char **line, int fd)
{
	size_t len;
	size_t i;

	i = g_row;
	len = ft_strlen(*line);
	while (i < len)
	{
		if ((*line)[i] == ' ' || (*line)[i] == '\t')
		{
			i++;
			continue;
		}
		else if ((*line)[i] == '"')
		{
			g_row = i + 1;
			return ;
		}
		else
			error_asm(NAME_INC, i, line, fd);
		i++;
	}
	error_asm(END_LINE_BTW_INSTR, g_row, line, fd);
}

static void	check_the_name(char **line, int fd)
{
	size_t i;
	size_t len;

	i = 0;
	len = ft_strlen(*line);
	while (i < len)
	{
		if ((*line)[i] == ' ' || (*line)[i] == '\t')
		{
			i++;
			continue ;
		}
		else if ((*line)[i] == '.' && ft_strnstr((*line) + i, NAME_CMD_STRING,
											ft_strlen(NAME_CMD_STRING)))
		{
			len = ft_strlen(NAME_CMD_STRING);
			if ((*line)[i + len] != ' ' && (*line)[i + len] != '\t')
				error_asm(WHIT_AF_TAB, i + len, line, fd);
			g_row = i + ft_strlen(NAME_CMD_STRING);
			return ;
		}
		else
			error_asm(WRONG_INSTR, i, line, fd);
	}
}

void		skip_whitespaces(int fd, char **line)
{
	size_t len;
	size_t count;

	while (get_next_line(fd, line) && ++g_count)
	{
		count = 0;
		len = ft_strlen(*line);
		while (count < len)
		{
			if ((*line)[count] == ' ' || (*line)[count] == '\t')
				count++;
			else if ((*line)[count] == COMMENT_CHAR || (*line)[count] == ';')
				break ;
			else
				return ;
		}
		ft_strdel(line);
	}
}

static char	*retrieve_name(int fd)
{
	char	*line;
	char	*out;
	t_list	*head;

	head = NULL;
	out = NULL;
	skip_whitespaces(fd, &line);
	if (line == NULL)
		exit(1);
	check_the_name(&line, fd);
	detect_the_beginning(&line, fd);
	fetch_the_name(&line, fd, g_row, &head);
	str_from_lsts(head, &out);
	if (ft_strlen(out) > PROG_NAME_LENGTH)
		error_asm(LONG_CHAMP_NAME, 0, NULL, fd);
	ft_lstdel(&head, free);
	return (out);
}

void		parse_name_and_comment(int fd, t_header *magic_structure)
{
	char	*tmp;

	ft_bzero(magic_structure->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(magic_structure->comment, COMMENT_LENGTH + 1);
	ft_strcpy(magic_structure->prog_name, tmp = retrieve_name(fd));
	if (!tmp)
		exit (1);
	if (ft_strlen(tmp) == 0)
	{
		ft_printf("{red}Name can't be blank.\n{eoc}");
		ft_strdel(&tmp);
		exit(1);
	}
	ft_strdel(&tmp);
	ft_strcpy(magic_structure->comment, tmp = retrieve_comment(fd));
	if (!tmp)
		exit (1);
	ft_strdel(&tmp);
}
