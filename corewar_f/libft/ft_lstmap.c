/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 18:40:53 by bcherkas          #+#    #+#             */
/*   Updated: 2017/11/23 13:38:40 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*maped;
	t_list	*head;

	if (lst == NULL || (f) == NULL)
		return (NULL);
	if ((maped = (f)(lst)) == NULL)
		return (NULL);
	lst = lst->next;
	head = maped;
	while (lst)
	{
		if ((f)(lst) == NULL)
		{
			ft_lstdel(&maped, ft_lstdelcontent);
			return (NULL);
		}
		head = ft_lstpushback(&head, (f)(lst));
		lst = lst->next;
	}
	return (maped);
}
