/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburlach <lburlach@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:41:35 by lburlach          #+#    #+#             */
/*   Updated: 2018/07/06 19:49:02 by lburlach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*check_filename(char *input_name)
{
	char	*ptr;
	char	*cor_name;

	if (!(ptr = ft_strrchr(input_name, '.')) || !(ft_strequ(ptr, ".s")))
		return (NULL);
	ptr = ft_strsub(input_name, 0, (size_t)(ptr - input_name));
	cor_name = ft_strjoin(ptr, ".cor");
	ft_strdel(&ptr);
	return (cor_name);
}

static void	initialize_globals(void)
{
	g_i = 0;
	g_count = 0;
	g_x = 0;
	g_code = NULL;
}

static void	main_wrapper(int ac, char **av, t_header *magic_structure,
							char **cor)
{
	int fd;
	int count;

	count = 1;
	while (count++ < ac)
	{
		initialize_globals();
		if (!((*cor) = check_filename(av[count - 1])))
		{
			ft_printf("File's extension does not end with \"s\"\n");
			exit(1);
		}
		fd = open(av[count - 1], O_RDONLY);
		if (fd == -1)
		{
			ft_printf("Cant read source file %s\n", av[count - 1]);
			exit(1);
		}
		parse_name_and_comment(fd, magic_structure);
		parse_code(fd);
		to_bytecode(magic_structure, cor);
		ft_printf("Writing output to file %s\n", (*cor));
		ft_strdel(cor);
		close(fd);
	}
}

int			main(int ac, char **av)
{
	t_header	magic_structure;
	char		*cor;

	if (ac == 1)
		usage();
	main_wrapper(ac, av, &magic_structure, &cor);
	system("leaks asm_dev");
	return (0);
}
