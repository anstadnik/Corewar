/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_name_and_comment.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:44:00 by lburlach          #+#    #+#             */
/*   Updated: 2018/06/06 20:59:46 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*second_stage_name_r(int fd, header_t *magic_structure)
{
	fd = 0;
	magic_structure = NULL;
	return (NULL);
}

static int	 check_the_name(char *line)
{
	size_t	i;
	size_t 	len;

	i = 0;
	len = ft_strlen(line);
	while (i < len)
	{
		if (line[i] == ' ' || line[i] == '\t')
		{
			i++;
			continue ;
		}
		else if (line[i] == '.' && ft_strstr(line + i + 1, "name"))
			return (1);
		else
			error_asm(WRONG_INSTR, i, line);
		i++;
	}
	return (0);
}

static char	*retrieve_name(int fd, header_t *magic_structure)
{
	char	*line;
	int 	flag;

	flag = 0;
	while (get_next_line(fd, &line) && ++g_count)
	{
		if (check_the_name(line))
		{
			flag++;
			break ;
		}
	}
	second_stage_name_r(0, magic_structure);
	return (NULL);
}

void		parse_name_and_comment(int fd, header_t *magic_structure)
{

	ft_bzero(magic_structure->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(magic_structure->comment, PROG_NAME_LENGTH + 1);
	ft_strcpy(magic_structure->prog_name, retrieve_name(fd, magic_structure));
	printf("prog_name = %s\n", magic_structure->prog_name);
}
