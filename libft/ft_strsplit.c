/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:50:31 by bcherkas          #+#    #+#             */
/*   Updated: 2017/11/22 12:24:54 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_getword(char *s, char c)
{
	size_t	len;
	char	*word;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	word = ft_strsub(s, 0, len);
	return (word);
}

static size_t	ft_countwords(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			i++;
		s++;
	}
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**arr;
	size_t	n;

	n = 0;
	if (s == NULL)
		return (0);
	arr = (char **)malloc(sizeof(char *) * (ft_countwords(s, c)) + 1);
	if (arr == NULL)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			if ((arr[n++] = ft_getword((char *)s, c)) == NULL)
			{
				ft_delarr(arr);
				return (NULL);
			}
		while (*s != c && *s)
			s++;
	}
	arr[n] = NULL;
	return (arr);
}
