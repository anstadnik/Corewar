/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 10:23:17 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/19 14:12:47 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

intmax_t	ft_pow(intmax_t n, int p)
{
	intmax_t	rez;

	if (p == 0)
		return (1);
	if (p < 0)
		return (-1);
	rez = 1;
	while (p--)
		rez *= n;
	return (rez);
}
