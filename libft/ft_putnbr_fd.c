/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:05:32 by bcherkas          #+#    #+#             */
/*   Updated: 2017/11/23 13:47:22 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fcntl.h"

void	ft_putnbr_fd(int n, int fd)
{
	int				dec;
	unsigned int	num;

	dec = 1;
	if (n < 0)
		ft_putchar_fd('-', fd);
	num = ft_abs(n);
	while (num > 9)
	{
		num /= 10;
		dec *= 10;
	}
	num = ft_abs(n);
	while (dec)
	{
		ft_putchar_fd(num / dec + '0', fd);
		num %= dec;
		dec /= 10;
	}
}
