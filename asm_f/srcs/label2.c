/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 19:58:00 by lburlach          #+#    #+#             */
/*   Updated: 2018/07/06 20:01:52 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			parse_labels(char **str, t_label **label, int fd)
{
	int	ret;

	if ((ret = parse_label(*str, label)) < 0)
		return (ret);
	while (skip_spaces(*str) == -1 && ret != 0 && *str)
	{
		ft_strdel(str);
		skip_empty(fd, str);
		if (!*str)
			return (1);
		if ((ret = parse_label(*str, label)) != 1 && ret != 0)
			return (ret);
	}
	return (1);
}

int			push_back_label(t_label **label, char *label_str)
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
