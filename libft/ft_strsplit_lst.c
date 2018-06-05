/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:24:08 by bcherkas          #+#    #+#             */
/*   Updated: 2017/11/22 12:27:36 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_getword(char *s, char c, int start)
{
	size_t	len;
	t_list	*word;

	len = 0;
	while (s[start + len] != c && s[start + len])
		len++;
	word = malloc(sizeof(t_list));
	if (word == NULL)
		return (NULL);
	if ((word->content = ft_strsub(s, start, len)) == NULL)
	{
		free(word);
		return (NULL);
	}
	word->content_size = len + 1;
	word->next = NULL;
	return (word);
}

t_list			*ft_strsplit_lst(char const *s, char c)
{
	t_list	*lst;
	size_t	i;

	lst = NULL;
	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			if (ft_getword((char *)s, c, i) == NULL)
			{
				ft_lstdel(&lst, ft_lstdelcontent);
				return (NULL);
			}
			ft_lstpushback(&lst, ft_getword((char *)s, c, i));
		}
		while (s[i] != c && s[i])
			i++;
	}
	return (lst);
}
