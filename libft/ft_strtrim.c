/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 17:37:46 by bcherkas          #+#    #+#             */
/*   Updated: 2017/11/22 12:29:30 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	end;

	if (s == NULL)
		return (NULL);
	start = 0;
	while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		start++;
	if (!s[start])
		return (ft_strsub(s, start, 0));
	end = ft_strlen((char *)s);
	while (s[end] == ' ' || s[end] == '\n' || s[end] == '\t' || !s[end])
		end--;
	end -= start;
	return (ft_strsub(s, start, end + 1));
}
