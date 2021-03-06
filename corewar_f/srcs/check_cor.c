/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 18:11:13 by bcherkas          #+#    #+#             */
/*   Updated: 2018/07/07 17:59:37 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_num(int fd)
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

void	cpy_to_map(t_info *inf, size_t size, unsigned char *str, int player)
{
	int		cpy_start;
	int		i;
	int		save;

	i = 0;
	save = 0;
	cpy_start = (MEM_SIZE / inf->players_amount) * player;
	ft_memcpy(inf->map + cpy_start, str, size);
	if (inf->args[FLAG_N] == 1)
		color_output(player + 1, str, cpy_start, size);
}

void	check_file(int fd, t_header *head, t_info *inf, int player)
{
	char			buff[4];
	unsigned char	str[CHAMP_MAX_SIZE];

	if (read(fd, buff, 0) < 0)
		errmsg("Cannot open file");
	if (get_num(fd) != COREWAR_EXEC_MAGIC)
		errmsg("No codage");
	head->prog_name[NAME_LEN] = 0;
	if (read(fd, head->prog_name, NAME_LEN) < NAME_LEN)
		errmsg("Wrong length");
	if (read(fd, buff, 4) < 4 || ft_memcmp(buff, "\0\0\0\0", 4))
		errmsg("No NULL group after name");
	if ((head->prog_size = (unsigned)get_num(fd)) > CHAMP_MAX_SIZE)
		errmsg("Too large file");
	head->comment[COMMENT_LEN] = 0;
	if (read(fd, head->comment, COMMENT_LEN) < COMMENT_LEN)
		errmsg("Wrong comment length");
	if (read(fd, buff, 4) < 4 || ft_memcmp(buff, "\0\0\0\0", 4))
		errmsg("No NULL group after comment");
	if (read(fd, str, head->prog_size) < head->prog_size)
		errmsg("Wrong program size");
	if (read(fd, buff, 1) > 0)
		errmsg("Padding error");
	cpy_to_map(inf, head->prog_size, str, player);
	close(fd);
}

void	read_players(t_info *inf)
{
	int		i;

	i = 0;
	while (i < inf->players_amount)
	{
		check_file(inf->players[i], &(inf->head[i]), inf, i);
		i++;
	}
}
