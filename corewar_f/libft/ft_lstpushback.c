/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 14:53:26 by bcherkas          #+#    #+#             */
/*   Updated: 2017/11/23 13:21:07 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpushback(t_list **alst, t_list *lst)
{
	t_list	*start;

	if (lst == NULL)
		return (NULL);
	start = *alst;
	if (start == NULL)
		*alst = lst;
	else
	{
		while (start->next)
			start = start->next;
		start->next = lst;
	}
	return (lst);
}
