/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:34:16 by bcherkas          #+#    #+#             */
/*   Updated: 2017/11/19 13:21:01 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*k;
	t_list	*s;

	s = NULL;
	k = *alst;
	if (*alst == NULL || (del) == NULL)
		return ;
	while (k)
	{
		s = k;
		del(k->content, k->content_size);
		k = k->next;
		free(s);
	}
	*alst = NULL;
}
