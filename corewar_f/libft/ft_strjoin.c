/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 17:32:27 by bcherkas          #+#    #+#             */
/*   Updated: 2018/03/12 19:07:21 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	end;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	end = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(sizeof(char) * end);
	if (str == NULL)
		return (NULL);
	if (s1)
		ft_strcpy(str, s1);
	if (s2)
		ft_strcat(str, s2);
	return (str);
}
