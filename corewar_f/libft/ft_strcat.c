/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 20:37:47 by bcherkas          #+#    #+#             */
/*   Updated: 2017/11/22 12:02:16 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	size_t	i;
	size_t	l;

	l = ft_strlen(s1);
	i = 0;
	while (s2[i])
	{
		s1[l] = s2[i];
		l++;
		i++;
	}
	s1[l] = '\0';
	return (s1);
}
