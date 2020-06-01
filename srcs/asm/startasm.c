/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startasm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:08:14 by faneyer           #+#    #+#             */
/*   Updated: 2020/05/24 20:53:23 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	create_string_for_parser_lexer(int fd, t_asm *master, char *av)
{
	char	*line;

	if (!(line = (char*)malloc(sizeof(char) * (16))))
		exit(0);
	ft_bzero(line, 16);
	if ((fd = open(av, O_RDONLY)) == -1)
		print_error_before_read("file don't exist\n",
		fd, master->buff_read, line);
	if (read_file(master, fd, line, 1) == -1)
		print_error_before_read("problem for read\n",
		fd, master->buff_read, line);
	close(fd);
}

void	free_token_and_buff(t_asm *master)
{
	free_tab_token(master);
	ft_strdel(&master->buff_read);
}

void	verif_option(t_asm *master, char **av)
{
	int	i;

	if (ft_strncmp(av[1], "-", 1) == 0 && ft_strlen(av[1]) <= 3 && av[1][1])
	{
		i = 1;
		while (av[1][i])
		{
			if (av[1][i] == 'l')
				master->option.t = 1;
			else if (av[1][i] == 'p')
				master->option.p = 1;
			else
			{
				print_usage();
				exit(0);
			}
			i++;
		}
	}
	else
	{
		print_usage();
		exit(0);
	}
}

void	end_asm(t_asm *master, char **av, int ac)
{
	if (master->error_parser == 0 && master->parser.name == 1 &&
		master->parser.comment == 1)
	{
		main_interpreteur(master, NULL);
		if (master->error_traitment == 0)
			init_write_file(master, av[ac - 1]);
	}
	if (master->parser.name == 0 && master->error_parser == 0 &&
		master->error_lexer == 0)
		ft_printf("need .name for compilation this champions\n");
	if (master->parser.comment == 0 && master->error_parser == 0 &&
		master->error_lexer == 0)
		ft_printf("need .comment for compilation this champions\n");
	free_undefine_label(master);
	free_define_label(master);
	free_token_and_buff(master);
}

int		main(int ac, char **av)
{
	t_asm	master;

	if (ac == 2 || ac == 3)
	{
		ft_bzero(&master, sizeof(t_asm));
		master.numline++;
		master.maxline++;
		if (ac == 3)
			verif_option(&master, av);
		init_op_tab((t_op*)(master.tab_op));
		verif_error_first(&master, av[ac - 1]);
		create_string_for_parser_lexer(0, &master, av[ac - 1]);
		main_lexer(&master, -1);
		if (master.option.t)
			print_token(&master, -1, NULL);
		main_parser(&master, NULL, -1);
		if (master.option.p)
			print_parser(&master, NULL, NULL);
		end_asm(&master, av, ac);
	}
	else
		print_usage();
	return (0);
}
