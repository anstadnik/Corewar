/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 17:24:55 by bcherkas          #+#    #+#             */
/*   Updated: 2017/11/22 12:28:19 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	k;
	size_t	n;

	i = 0;
	k = 0;
	n = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[n])
	{
		i = 0;
		k = n;
		while (haystack[n] == needle[i])
		{
			n++;
			i++;
			if (!needle[i])
				return ((char *)(haystack + n - i));
		}
		n = k + 1;
	}
	return (NULL);
}
