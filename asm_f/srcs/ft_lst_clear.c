/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 16:31:39 by lburlach          #+#    #+#             */
/*   Updated: 2018/01/12 13:39:46 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_clear(t_list **alst)
{
	t_list *tmp;

	if (!alst || !(*alst))
		return ;
	while (*alst)
	{
		tmp = *alst;
		(*alst) = (*alst)->next;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = NULL;
	}
	*(alst) = NULL;
}
