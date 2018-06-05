/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 20:07:55 by bcherkas          #+#    #+#             */
/*   Updated: 2017/11/14 16:02:48 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int				min;
	unsigned long	sum;

	sum = 0;
	min = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		min *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && ft_isdigit(*str))
	{
		if ((sum >= 922337203685477580 || (sum == 922337203685477580 &&
						(*str - '0') > 7)) && min == 1)
			return (-1);
		else if ((sum >= 922337203685477580 || (sum == 922337203685477580 &&
					(*str - '0') > 8)) && min == -1)
			return (0);
		sum = sum * 10 + (*str - '0');
		str++;
	}
	return ((int)sum * min);
}
