/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:54:28 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/15 13:54:42 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LST_H
# define FT_LST_H

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				ft_lstaddb(t_list **head, t_list *list);
void				ft_lstadd(t_list **alst, t_list *elem);
void				ft_lstpushb(t_list **list, void *content,
		size_t content_size);
void				ft_lstdel(t_list **alst, void (*del)(void *));
void				ft_lstdelone(t_list **aslt, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstgetlast(t_list *head);
void				ft_lstpushf(t_list **alst, void *content,
		size_t content_size);
void				ft_lstdelnode(t_list **head, t_list *targ);
char				*ft_lsttostr(t_list *head);
ssize_t	            str_from_lsts(t_list *tmp, char **line);

#endif
