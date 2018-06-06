/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:30:00 by lburlach          #+#    #+#             */
/*   Updated: 2018/06/06 16:07:14 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ASM_H
# define ASM_H

#include "libft.h"
#include "op.h"
#include <fcntl.h>

void	parse_name_and_comment(int fd, header_t *magic_structure);
void	usage(void);
void	error_ac(char *s);
void	error_asm(char *err, size_t y, size_t x, char *code);

#endif
