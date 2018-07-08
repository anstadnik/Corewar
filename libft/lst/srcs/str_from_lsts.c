/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_from_lsts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:58:07 by lburlach          #+#    #+#             */
/*   Updated: 2018/03/14 14:00:25 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	str_from_lsts(t_list *tmp, char **line)
{
	t_list			*beg;
	size_t			i;
	size_t			c;

	c = 0;
	beg = tmp;
	while (beg)
	{
		c += beg->content_size;
		beg = beg->next;
	}
	(*line) = ft_memalloc(c + 1);
	if (*line == NULL)
		return (-1);
	i = 0;
	while (tmp)
	{
		ft_memcpy(&(*line)[i], tmp->content, tmp->content_size);
		i += (tmp->content_size);
		tmp = tmp->next;
	}
	return (c);
}
