/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byermak <byermak@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:41:35 by lburlach          #+#    #+#             */
/*   Updated: 2018/07/02 16:32:36 by byermak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*check_filename(char *input_name)
{
	char	*ptr;
	char	*cor_name;

	if (!(ptr = ft_strrchr(input_name, '.')) || !(ft_strequ(ptr, ".s")))
		return (NULL);
	ptr = ft_strsub(input_name, 0, (size_t)(ptr - input_name));
	cor_name = ft_strjoin(ptr, ".co");//TODO .cor
	ft_strdel(&ptr);
	return (cor_name);
}

int		main(int ac, char **av)
{
	t_header	magic_structure;
	int			fd;
	char		*cor;
	int			out_fd;

	if (ac == 1)
		usage();
	else if (ac > 2)
		error_ac(av[ac - 1]);
	if (!(cor = check_filename(av[1])))
		ft_printf("test");///error (file not .s);
	fd = open(av[ac - 1], O_RDONLY);
	//error if fd == -1 ?
	parse_name_and_comment(fd, &magic_structure);
//	ft_printf("%i\n", g_count);
	g_code = NULL;
	parse_code(fd);
	out_fd = open(cor, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
	ft_strdel(&cor);
	to_bytecode(&magic_structure, out_fd);
	close(out_fd);
	close(fd);
//	system("leaks asm_dev");
	return (0);
}
