/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 18:11:13 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/07 17:57:00 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

size_t	get_num(int fd)
{
	t_magic	uni;
	int		i;

	i = 0;
	while (i < 4)
	{
		if (read(fd, &uni.arr[3 - i], 1) == 0)
			errmsg("Wrong file");
		i++;
	}
	return (uni.magic);
}

void	print_info(int start, char *str, int size)
{
	int		i;

	i = 0;
	printf("%d\n", start);
	while (i < size)
	{
		printf("%3.2hhx", str[i]);
		i++;
	}
	printf("\n");
}

void	cpy_to_map(t_info *inf, size_t size, char *str, int player)
{
	int		cpy_start;

	cpy_start = (MEM_SIZE / inf->players) * player;
	ft_memcpy(inf->map + cpy_start, str, size);
//	print_info(cpy_start, str, size);
}

/*
 * Add beautiful output
 */

void	check_file(int fd, t_header *head, t_info *inf, int player)
{
	char	buff[4];
	char	str[CHAMP_MAX_SIZE];

	if (read(fd, buff, 0) < 0)
		errmsg("Cannot open file");
	if (get_num(fd) != COREWAR_EXEC_MAGIC)
		errmsg("Wrong file");
	head->prog_name[NAME_LEN] = 0;
	if (read(fd, head->prog_name, NAME_LEN) < NAME_LEN)
		errmsg("Wrong file");
	if (read(fd, buff, 4) < 4 || ft_memcmp(buff, "\0\0\0\0", 4))
		errmsg("Wrong file");
	head->prog_size = (unsigned)get_num(fd);
	head->comment[COMMENT_LEN] = 0;
	if (read(fd, head->comment, COMMENT_LEN) < COMMENT_LEN)
		errmsg("Wrong file");
	if (read(fd, buff, 4) < 4 || ft_memcmp(buff, "\0\0\0\0", 4))
		errmsg("Wrong file");	
	if (read(fd, str, head->prog_size) < head->prog_size)
		errmsg("Wrong file");
	if ((head->prog_size % 2 == 0 && read(fd, buff, 4) > 0) ||
		(head->prog_size % 2 != 0 && read(fd, buff, 4) > 1))// Check this
		errmsg("Wrong file");
	cpy_to_map(inf, head->prog_size, str, player);
	close(fd);
}

void	read_players(t_info *inf)
{
	int		i;

	i = 0;
	while (i < inf->players)
	{
		check_file(inf->fd[i], &(inf->head[i]), inf, i);
		i++;
	}
}
