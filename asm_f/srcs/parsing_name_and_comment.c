/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_name_and_comment.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:44:00 by lburlach          #+#    #+#             */
/*   Updated: 2018/06/09 19:53:05 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
//TODO:
#include <stdio.h>


static size_t g_row;

static void	detect_the_beginning(char **line)
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
			return;
		}
		else
			error_asm(NAME_INC, i, line);
		i++;
	}
	error_asm(END_LINE_BTW_INSTR, g_row, line);
}

static void	check_the_name(char **line)
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
				error_asm(WHIT_AF_TAB, i + len, line);
			g_row = i + ft_strlen(NAME_CMD_STRING);
			return ;
		}
		else
			error_asm(WRONG_INSTR, i, line);
	}
}

void	skip_whitespaces(int fd, char **line)
{
	size_t len;
	size_t count;

	while (get_next_line(fd, line))
	{
		count = 0;
		len = ft_strlen(*line);
		while (count < len)
		{
			if ((*line)[count] == ' ' || (*line)[count] == '\t')
				count++;
			else
				return;
		}
		g_count++;
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
	check_the_name(&line);
	detect_the_beginning(&line);
	fetch_the_name(&line, fd, g_row, &head);
	str_from_lsts(head, &out);
	printf("length = %ld\n", ft_strlen(out));
	if (ft_strlen(out) > PROG_NAME_LENGTH)
		error_asm(LONG_CHAMP_NAME, 0, NULL);
	printf("out = %s\n--//--\n", out);
	return (out);
}

void		parse_name_and_comment(int fd, t_header *magic_structure)
{
	ft_bzero(magic_structure->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(magic_structure->comment, COMMENT_LENGTH + 1);
	ft_strcpy(magic_structure->prog_name, retrieve_name(fd));
	ft_strcpy(magic_structure->comment, retrieve_comment(fd));
	printf("\n\n\n");
	printf("prog_name = %s\n", magic_structure->prog_name);
	printf("comment = %s\n", magic_structure->comment);
}
