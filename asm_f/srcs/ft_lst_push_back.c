/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:18:40 by lburlach          #+#    #+#             */
/*   Updated: 2017/12/11 16:43:34 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** It'll add an element into the end of a list.
*/

void	ft_lst_push_back(t_list **tmp, void *data, size_t con_s)
{
	t_list *hm;
	t_list *kek;

	if (!tmp)
		return ;
	kek = *tmp;
	hm = ft_lstnew((void *)data, con_s);
	if (hm == NULL)
		return ;
	if (!(*tmp))
	{
		*tmp = hm;
		return ;
	}
	while (kek->next)
		kek = kek->next;
	kek->next = hm;
}
