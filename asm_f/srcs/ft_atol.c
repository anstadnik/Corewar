/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 14:26:43 by astadnik          #+#    #+#             */
/*   Updated: 2018/07/05 21:05:24 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The atoi() function converts the initial portion of the string pointed to by
** str to int representation.
*/

#include "libft.h"

long long	ft_atol(const char *s)
{
	char				neg;
	long long	rez;

	rez = 0;
	neg = 0;
	while (ft_iswhitespace(*s))
		s++;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			neg = 1;
	while (*s == '0')
		s++;
	while (ft_isdigit(*s))
	{
		rez = rez * 10 + (unsigned long long)(*s++ - '0');
	}
	return (neg ? -1 * (long long)rez : (long long)rez);
}
