/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_name_and_comment2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:54:00 by lburlach          #+#    #+#             */
/*   Updated: 2018/07/08 20:04:04 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static size_t g_row;

static	int	search_the_end(char **line, size_t *row, t_list **head, size_t len)
{
	size_t tmp;

	tmp = *row;
	while (tmp < len)
	{
		if ((*line)[tmp] == '"')
		{
			ft_lstpushb(head, (*line + *row), tmp - *row);
			*row += tmp - *row + 1;
			return (1);
		}
		tmp++;
	}
	ft_lstpushb(head, (*line + *row), tmp - *row);
	ft_lstpushb(head, "\n", 1);
	*row += tmp;
	return (0);
}

void		fetch_the_name(char **line, int fd, size_t row, t_list **head)
{
	size_t	len;
	size_t	count;
	int		ret;

	count = 0;
	while (++count)
	{
		if (count > 1)
			row = 0;
		len = ft_strlen(*line);
		if (search_the_end(line, &row, head, len))
			break ;
		ft_strdel(line);
		ret = get_next_line(fd, line);
		if (ret == 0 && ++g_count)
			error_asm(UNSUF_INFO, row, line, fd);
	}
	count = row;
	while (count < len)
	{
		if ((*line)[count] != ' ' && (*line)[count] != '\t')
			error_asm(WRONG_INSTR, count, line, fd);
		count++;
	}
	ft_strdel(line);
}

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
		else if ((*line)[i] == '.' && ft_strnstr((*line) + i,
			COMMENT_CMD_STRING,
			ft_strlen(COMMENT_CMD_STRING)))
		{
			len = ft_strlen(COMMENT_CMD_STRING);
			if ((*line)[i + len] != ' ' && (*line)[i + len] != '\t')
				error_asm(WHIT_AF_TAB_C, i + len, line, fd);
			g_row = i + ft_strlen(COMMENT_CMD_STRING);
			return ;
		}
		else
			error_asm(WRONG_INSTR, i, line, fd);
	}
}

char		*retrieve_comment(int fd)
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
	if (ft_strlen(out) > COMMENT_LENGTH)
		error_asm(LONG_CHAMP_NAME, 0, NULL, fd);
	ft_lstdel(&head, free);
	return (out);
}
