/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:16:00 by byermak           #+#    #+#             */
/*   Updated: 2018/06/16 14:20:54 by byermak          ###   ########.fr       */
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

char		*parse_label(char *str)
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

int			check_labels(t_code *tmp, int label_index)
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
