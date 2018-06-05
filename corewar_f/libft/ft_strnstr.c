/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 18:13:37 by bcherkas          #+#    #+#             */
/*   Updated: 2017/11/19 18:22:44 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n;
	size_t	k;

	i = 0;
	n = 0;
	k = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (n < len && haystack[n])
	{
		i = 0;
		k = n;
		while (haystack[n] == needle[i] && n < len)
		{
			n++;
			i++;
			if (!needle[i])
				return ((char *)haystack + n - i);
		}
		n = k + 1;
	}
	return (NULL);
}
