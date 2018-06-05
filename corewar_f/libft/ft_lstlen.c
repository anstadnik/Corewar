/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 18:42:35 by bcherkas          #+#    #+#             */
/*   Updated: 2017/11/17 18:50:53 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstlen(t_list *alst)
{
	int		i;

	i = 1;
	if (alst == NULL)
		return (0);
	while (alst->next)
	{
		i++;
		alst = alst->next;
	}
	return (i);
}
