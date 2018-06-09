/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:30:00 by lburlach          #+#    #+#             */
/*   Updated: 2018/06/09 19:25:14 by lburlach         ###   ########.fr       */
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
void	error_asm(int err_num, size_t x, char **code);
void	fetch_the_name(char **line, int fd, size_t row, t_list **head);
char	*retrieve_comment(int fd);
void	skip_whitespaces(int fd, char **line);

size_t	g_count;

enum g_err {
	WRONG_INSTR = 1,
	READING_ERR,
	NAME_INC,
	WHIT_AF_TAB,
	UNSUF_INFO,
	LONG_CHAMP_NAME,
	WHIT_AF_TAB_C,
	END_LINE_BTW_INSTR,

};

#endif
