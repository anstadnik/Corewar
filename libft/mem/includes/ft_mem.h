/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:57:50 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/15 14:40:28 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEM_H
# define FT_MEM_H

void	ft_bzero(void *s, size_t n);
void	*ft_realloc(void *ptr, size_t size_src, size_t size);
void	*ft_memdup(void *src, size_t size);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *str, int c, size_t n);
void	*ft_memccpy(void *s1, void const *s2, int c, size_t n);
void	*ft_memset(void *str, int c, size_t n);
void	*ft_memcpy(void *str1, const void *str2, size_t n);
void	*ft_memalloc(size_t size);
void	ft_memdel(void **ap);
void	*ft_memmove(void *s1, const void *s2, size_t n);

#endif
