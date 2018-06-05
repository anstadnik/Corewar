/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 18:28:44 by bcherkas          #+#    #+#             */
/*   Updated: 2017/11/22 12:20:32 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*arr;

	i = 0;
	if (s == NULL || (f) == NULL)
		return (NULL);
	while (s[i])
		i++;
	if ((arr = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		arr[i] = ((f)(i, s[i]));
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
