/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:32:47 by bcherkas          #+#    #+#             */
/*   Updated: 2017/11/23 13:47:08 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int				dec;
	unsigned int	num;

	dec = 1;
	if (n < 0)
		ft_putchar('-');
	num = ft_abs(n);
	while (num > 9)
	{
		num /= 10;
		dec *= 10;
	}
	num = ft_abs(n);
	while (dec)
	{
		ft_putchar(num / dec + '0');
		num %= dec;
		dec /= 10;
	}
}
