/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 15:33:54 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/15 14:03:59 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Puts the next string from appropriate fd list to the line. If more reading
** is needed, returns 2. If there is a full string, returns it and deletes node
** from the linked list.
*/

static int		get_rest(int fd, char **line, t_list **head)
{
	t_list	*tmp;
	t_list	*cur;
	size_t	finished;

	*line = NULL;
	cur = *head;
	while (cur && (int)cur->content_size != fd)
		cur = cur->next;
	if (!cur || !cur->content)
		return (2);
	*line = ((t_list *)cur->content)->content;
	tmp = (t_list *)cur->content;
	finished = tmp->content_size;
	cur->content = ((t_list *)cur->content)->next;
	free(tmp);
	if (finished)
		return (1);
	return (2);
}

/*
** Fills the getlist with lists if needed. Also changes the status flag
** of getlist.
*/

static int		fill_rest(t_list *cur, char **line)
{
	char	*beg;
	char	*end;
	char	*temp;
	t_list	**content;

	temp = *line;
	beg = ft_strchr(*line, '\n');
	content = (t_list **)&cur->content;
	*line = ft_strsub(temp, 0, beg ? (size_t)(beg++ - temp) : ft_strlen(temp));
	while (beg && *beg)
	{
		end = ft_strchr(beg, '\n');
		if (!(*content = ft_lstnew(beg,
				end ? (size_t)(end - beg) + 1 : ft_strlen(beg) + 1)))
			return (-1);
		if (end)
			((char*)((*content)->content))[(size_t)(end - beg)] = '\0';
		(*content)->content_size = end ? 1 : 0;
		content = &(*content)->next;
		beg = end ? end + 1 : NULL;
	}
	free(temp);
	return (1);
}

/*
** Reads from input untill \n is finded, then fills the list.
*/

static ssize_t	read_line(int fd, ssize_t f, char **line, size_t size)
{
	size_t		i;
	char		str[BUFF_SIZE + 1];

	i = *line ? ft_strlen(*line) : 0;
	*line = ft_realloc(*line, *line ? ft_strlen(*line) + 1 : 0, size);
	(*line)[i] = '\0';
	while (f == 42 && i + BUFF_SIZE < size)
	{
		if ((f = read(fd, str, BUFF_SIZE)) == -1)
		{
			ft_memdel((void **)line);
			return (-1);
		}
		str[f] = 0;
		ft_memcpy(*line + i, str, (size_t)f + 1);
		i += (size_t)f;
		if (ft_strchr(*line, '\n'))
			f = 1;
		else
			f = f == BUFF_SIZE ? 42 : 0;
	}
	size *= 2;
	return (f);
}

static int		read_more(int fd, char **line, t_list **head)
{
	t_list		**cur;
	size_t		size;
	ssize_t		f;

	cur = head;
	while (*cur && (int)(*cur)->content_size != fd)
		cur = &(*cur)->next;
	f = 42;
	size = BUFF_SIZE;
	while ((f = read_line(fd, f, line, size)) == 42)
		size *= 2;
	if (f == -1 || (f == 0 && !**line))
	{
		ft_memdel((void **)line);
		if (*cur)
			ft_lstdelnode(head, *cur);
		return ((int)f);
	}
	if (!*cur && !(*cur = ft_memalloc(sizeof(t_list))))
	{
		ft_memdel((void **)line);
		return (-1);
	}
	(*cur)->content_size = (size_t)fd;
	return (fill_rest(*cur, line));
}

/*
** Main function
*/

int				get_next_line(const int fd, char **line)
{
	static t_list	*head;
	int				rez;

	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	rez = get_rest(fd, line, &head);
	return (rez == 2 ? read_more(fd, line, &head) : rez);
}
