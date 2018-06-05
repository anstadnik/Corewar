/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:17:17 by bcherkas          #+#    #+#             */
/*   Updated: 2017/11/23 13:46:41 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char			*arr;
	int				i;
	unsigned int	s;

	i = 0;
	i = ft_intlen(n);
	if (n < 0)
		i++;
	arr = ft_strnew(i);
	if (arr == NULL)
		return (NULL);
	if (n < 0)
		arr[i - 1] = '-';
	i = 0;
	s = ft_abs(n);
	if (s == 0 || n == -0)
		arr[i] = '0';
	while (s != 0)
	{
		arr[i++] = (s % 10) + '0';
		s /= 10;
	}
	ft_strrev(arr);
	return (arr);
}
