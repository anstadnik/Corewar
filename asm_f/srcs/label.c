/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:16:00 by byermak           #+#    #+#             */
/*   Updated: 2018/07/05 19:39:00 by byermak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
	t_label	*label_tmp;

	tmp = g_code;
	while (tmp)
	{
		if (tmp->label)
		{
			label_tmp = tmp->label;
			while (label_tmp)
			{
				if (ft_strequ(label_tmp->label, label))
				{
					ft_strdel(&label);
					return (NULL);
				}
				label_tmp = label_tmp->next;
			}
		}
		tmp = tmp->next;
	}
	return (label);
}

int		push_back_label(t_label **label, char *label_str)
{
	t_label *new;
	t_label	*tmp;

	if (!(new = (t_label *)malloc(sizeof(t_label))))
		return (ERR_MALLOC);
	new->label = ft_strdup(label_str);
	new->next = NULL;
	if (!*label)
	{
		*label = new;
		return (1);
	}
	tmp = *label;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

int		parse_label(char *str, t_label **label)
{
	char	*tmp;
	char	*label_str;
	size_t	i;
	int		ret;

	i = g_x;
	tmp = ft_strchr(str, LABEL_CHAR);
	if (!tmp)
		return (0);
	while ((str + i) != tmp)
		if (!check_label_words(str[i++]))
			return (0);
	label_str = check_label(ft_strsub(str,
			(unsigned int)g_x, (size_t)(tmp - (str + g_x))));
	g_x += ft_strlen(label_str) + 1;
	if ((ret = push_back_label(label, label_str)) != 1)
	{
		del_labels(label);
		return (ret);
	}
	ft_strdel(&label_str);
	return (1);
}

static int	find_label(char *label, t_label *last)
{
	t_code	*tmp;
	t_label	*label_tmp;

	tmp = g_code;
	while (tmp)
	{
		if (tmp->label)
		{
			label_tmp = tmp->label;
			while (label_tmp)
			{
				if (ft_strequ(label_tmp->label, label))
					return (tmp->index);
				label_tmp = label_tmp->next;
			}
		}
		tmp = tmp->next;
	}
	if (last && ft_strequ(label, last->label))
		return (get_prog_size());
	return (-1);
}

int			check_labels(t_code *tmp, int label_index, t_label **last)
{
	tmp = g_code;
	while (tmp)
	{
		if (tmp->arg1->label_flag)
		{
			if ((label_index = find_label(tmp->arg1->label, *last)) == -1)
				return (label_error());
			tmp->arg1->value = (unsigned short)label_index - tmp->index;
		}
		if (tmp->arg2 && tmp->arg2->label_flag)
		{
			if ((label_index = find_label(tmp->arg2->label, *last)) == -1)
				return (label_error());
			tmp->arg2->value = (unsigned short)label_index - tmp->index;
		}
		if (tmp->arg3 && tmp->arg3->label_flag)
		{
			if ((label_index = find_label(tmp->arg3->label, *last)) == -1)
				return (label_error());
			tmp->arg3->value = (unsigned short)label_index - tmp->index;
		}
		tmp = tmp->next;
	}
	del_labels(last);
	return (1);
}
